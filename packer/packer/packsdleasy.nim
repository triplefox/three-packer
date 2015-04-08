import sdl2
import sdl2.image
import packsdl
import pack
import json
import tables

type
  BundleTup* = tuple[surf:SurfacePtr,sb:SheetBundle]

proc loadImage*(filename:string):SurfacePtr=
  var suce = load(cstring(filename))  
  if suce == nil:
    var err = new Exception
    err.msg = "Failed to load \""&filename&"\": "&($getError())
    raise err
  return suce

proc packSheet*(isurf, og, osurf, croppedassets):seq[Asset]=
  result = og.packScanline(croppedassets)
  osurf.copy(isurf, result)
proc packBundle*(abd : SheetBundle, og : AssetGroup):seq[BundleTup]=
  result = @[]
  var aseq = og.multipackScanline(abd.asset)
  for a0 in aseq:
    var osurf = newSurface(og.rect)
    var sb0 : SheetBundle; new(sb0)
    sb0.group = abd.group
    sb0.surf = abd.surf
    sb0.asset = a0
    osurf.copy(sb0)
    result.add((surf:osurf,sb:sb0))
proc tileBundle*(abd : SheetBundle, og : AssetGroup, w0:int, h0:int):seq[BundleTup]=
  result = @[]
  var remainder = abd.asset
  for r0 in remainder.fitsInTileSize(w0, h0):
    echo("$1 doesn't fit in tile size $2,$3" % [$r0, $w0, $h0])
  while remainder.len > 0:
    var tiling0 = og.rHorizTiling(w0,h0)
    var working : seq[Asset]
    if tiling0.len >= remainder.len:
      working = remainder
      remainder = @[]
    else:
      working = remainder[0.. tiling0.high]
      remainder = remainder[tiling0.len.. remainder.high]
    var a0 = og.packToRectsC(working, tiling0)
    var osurf = newSurface(og.rect)
    var sb0 : SheetBundle; new(sb0)
    sb0.group = abd.group
    sb0.surf = abd.surf
    sb0.asset = a0
    osurf.copy(sb0)
    sb0.asset = og.packToRectsC(working, tiling0) 
    result.add((surf:osurf,sb:sb0))

proc JSONDataEntry*(ds : seq[pack.DataEntry]):JsonNode=
  if ds == nil:
    return newJArray()
  var ja0 = newJArray()
  for d0 in ds:
    var ja1 = newJArray()
    ja1.add(newJString(d0.k))
    ja1.add(newJInt(d0.v))
    ja0.add(ja1)
  return ja0
proc ofJSONDataEntry*(ja : JsonNode):seq[pack.DataEntry]=
  result = @[]
  for d0 in ja:
    result.add(newData(d0[0].str,int(d0[1].num)))
proc JSONRect*(r0 : pack.Rect):JsonNode=
  var ja = newJArray()
  ja.add(newJInt(r0.x))
  ja.add(newJInt(r0.y))
  ja.add(newJInt(r0.w))
  ja.add(newJInt(r0.h))
  ja.add(JSONDataEntry(r0.d))
  return ja
proc ofJSONRect*(ja : JsonNode):pack.Rect=
  return newRect(int(ja[0].num),
    int(ja[1].num), int(ja[2].num), int(ja[3].num),
    ofJSONDataEntry(ja[4]))
type
  AssetJSONManifest* = tuple[
    asset:OrderedTable[int,Asset],
    group:OrderedTable[int,AssetGroup],
    json:JsonNode
    ]

proc saveJSON*(asset : seq[Asset], fn : string):AssetJSONManifest=
  var atbl = initOrderedTable[int, Asset]()
  var gtbl = initOrderedTable[int, AssetGroup]()
  var ga = newJArray();
  var aa = newJArray();
  for a0 in asset:
    # check for colliding asset
    if atbl.hasKey(a0.i):
      var ex = new Exception
      ex.msg = "collision: two different assets identified #"&($a0.i)
      raise ex
    else:
      atbl[a0.i] = a0
      var aobj = newJObject()
      aobj.add("i",newJInt(a0.i))
      aobj.add("g",newJInt(a0.g.id))
      var ra = newJArray()
      for r0 in a0.r:
        ra.add(JSONRect(r0))
      aobj.add("r",ra)
      aa.add(aobj)
    # check for colliding group
    if gtbl.hasKey(a0.g.id):
      if gtbl[a0.g.id] != a0.g:
        var ex = new Exception
        ex.msg = "collision: two different output groups identified #"&($a0.g.id)&
          ": "&gtbl[a0.g.id].name&", "&a0.g.name 
        raise ex
    else:
      gtbl[a0.g.id]= a0.g
      var gobj = newJObject()
      gobj.add("rect", JSONRect(a0.g.rect))
      gobj.add("name", newJString(a0.g.name))
      gobj.add("counter", newJInt(a0.g.counter))
      gobj.add("id", newJInt(a0.g.id))
      ga.add(gobj)
  var jobj = newJObject()
  jobj.add("group",ga)
  jobj.add("asset",aa)
  return (asset:atbl, group:gtbl, json:jobj)

proc loadJSON*(jobj : JsonNode):AssetJSONManifest=
  var atbl = initOrderedTable[int, Asset]()
  var gtbl = initOrderedTable[int, AssetGroup]()
  var gobj = jobj["group"]
  var aobj = jobj["asset"]
  for g in gobj:
    var ag : AssetGroup; new(ag); 
    ag.id = int(g["id"].num); 
    gtbl.add(ag.id, ag)
    ag.name = g["name"].str; 
    ag.rect = ofJSONRect(g["rect"]) 
    ag.counter = int(g["counter"].num);
  var i0 = 0
  for a in aobj:
    var ra = newSeq[pack.Rect](a["r"].len)
    for r0 in a["r"]:
      ra.add(ofJSONRect(r0))
    var na = newAsset(int(a["i"].num),
      gtbl[int(a["g"].num)],
      ra)
    atbl[i0]=na
    i0 += 1
  return (asset:atbl, group:gtbl, json:jobj)

proc getTiles*(ig, isurf, tw, th):seq[Asset]=
  var tiles = ig.rHorizTiling(tw,th) # get rectangles
  result = newSeq[Asset](0) # create a cropped set of assets
  for n0 in 0.. tiles.high:
    var a0 = newAsset(n0, ig, @[tiles[n0]]) # new asset containing the tile rectangle
    a0.reduce(isurf, 0x000000FF, Smallest) # crop to smallest-fit
    if not a0.isEmpty(isurf, 0x000000FF): # only include if result has pixels
      result.add(a0)
