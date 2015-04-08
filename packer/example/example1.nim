import json
import math
import sdl2
import sdl2.image
import pack
import packsdl
import packsdleasy
import algorithm

discard image.init

proc test()=
  # some testing code
  block:
    var filename = "test000.json"
    var jsona = parseFile(filename); echo(jsona)
  var o = newAssetGroup("MyGroup", newRect(0,0,256,256))
  var pg0 : seq[Asset] = @[]
  var pg1 : seq[Asset] = @[]
  var p0 = newAsset(0, o, @[newRect(0,0,8,8,@[newData("Radius",10)])]); pg0.add(p0)
  var p1 = newAsset(1, o, @[newRect(0,0,8,8,@[newData("Radius",60)])]); pg1.add(p1)
  var p2 = p0.copy; pg1.add(p2)
  p0.r[0].d["after"]=2
  echo(pg0)
  echo(pg1)

  proc fn0(r : pack.Rect):bool = len(r.d["Radius"])>0
  echo(pg1.viewAssetRects(fn0))

  var ts : seq[DataEntry] = @[]

  ts.add("hello", 1)
  ts.add("mello", 2)
  echo(ts)
  ts.add("hello", 3)
  echo(ts)
  echo(ts["hello"])
  ts["mello"]=4
  echo(ts)

  echo(o.rHorizTiling(128,128))
  echo "..."
  echo(o.rHorizTiling(128,128,-128,-128,128,128))
  echo "..."
  echo(o.rWidths(@[128,128,128,128],128))
  echo "..."
  echo(o.rWidths(@[128,128,128,128],128,false,-128,128,128))
  echo "..."
  echo(o.rVertTiling(128,128))
  echo "..."
  echo(o.rVertTiling(128,128,-128,-128,128,128))
  echo "..."
  echo(o.rHeights(@[128,128,128,128],128))
  echo "..."
  echo(o.rHeights(@[128,128,128,128],128,false,-128,128,128))
  echo "rects0:"
  echo(o.assetsOfRects(@[[0,0,128,128],[128,0,128,128],[0,128,128,128],[128,128,128,128]]))
  echo "rects1:"
  echo(o.assetsOfRects(@[0,0,128,128,128,0,128,128,0,128,128,128,128,128,128,128]))
  echo "rects2:"
  echo(o.assetsOfRects(@[newRect(0,0,128,128),newRect(128,0,128,128),
    newRect(0,128,128,128),newRect(128,128,128,128)]))

  p0.r.reduce(2,2,2,2)
  echo(p0.r)

  echo(@(minSizeOfAssets(pg1,10,0)))
  echo(packToRectsTL(o,pg1,o.rHorizTiling(16,16)))
  echo(packToRectsC(o,pg1,o.rHorizTiling(16,16)))
  var m0 = packToRectsGrowC(o,pg1,o.rHorizTiling(16,16)) 
  echo(m0)
  echo(@[m0[0].p,m0[1].p])
  
  echo(aabb(0,0,8,8, 0,0,1,1))
  echo(aabb(0,0,8,8, 9,0,1,1))
  echo(aabb(0,0,8,8, -1,0,1,1))
  echo(aabb(0,0,8,8, -2,0,1,1))
  echo(aabb(0,0,8,8, 0,-1,1,1))
  echo(aabb(0,0,8,8, 0,-2,1,1))
  echo(aabb(0,0,8,8, 0,-9,1,1))

  var pg2 : seq[Asset] = @[]
  for i0 in 0.. 30:
    pg2.add(o.newTestAsset(0,0,5+math.random(50),5+math.random(50)))
  echo(packScanline(o, pg2).pack)  

proc doClear(renr : RendererPtr)=
  renr.setDrawColor(uint8(math.random(64)), 
          uint8(math.random(64)), 
          uint8(math.random(64)), 255)
  renr.clear()

proc display()=
  discard sdl2.init(INIT_EVERYTHING)
  var wiow = createWindow(
    "Sprite Sheets!",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    640, 480,
    SDL_WINDOW_SHOWN)
    
  var surftiles32 = loadImage("jerom-fantasy-tileset-32.png");
  var surftiles16 = loadImage("jerom-fantasy-tileset-16.png");
  var surftiles8 = loadImage("jerom-fantasy-tileset-8.png");
  var surftiles16_2 = loadImage("joecreates-roguelikeitems-1.png");
  #var alpha = MapRGBA(surftiles32.format, 0, 0, 0, 0xFF)
  #(MapRGBA doesn't seem to work well when the original surface is indexed color.)
  var alpha = uint32(0x000000FF)

  const use_speedy = false
  const skipstride = 1

  var evnt:Event
  var renr = createRenderer(wiow, -1, 0);

  proc drawCopy(g : AssetGroup, count : int, basex : int, basey : int, randomx : int, randomy : int)=
    var surf = newSurface(g.rect)
    var pg0 : seq[Asset] = @[]
    for i0 in 0.. <(count):
      let w0 = (if randomx > 0: (math.random(randomx)+basex) else: basex)
      let h0 = (if randomy > 0: (math.random(randomy)+basey) else: basey)
      pg0.add(g.newTestAsset(0,0,w0,h0))
    var manifest = g.packScanline(pg0, skipstride, use_speedy, true) 
    pg0 = manifest.pack
    if manifest.remainder != nil:
      echo("missed "&($manifest.remainder.len)&" rects")
    surf.drawColors(pg0)
    renr.doClear()
    renr.copy(surf, nil, g.rect)
    surf.destroy()
  proc drawCrops(g : AssetGroup)=
    var surf = newSurface(g.rect)
    var ta = g.newTestAsset(math.random(128),math.random(128),math.random(128),math.random(128))
    surf.drawColors(@[ta])
    let a0 = newAsset(0, g, @[g.rect])
    renr.doClear()
    renr.copy(surf, nil, g.rect)

    var sml = a0.copy(); sml.reduce(surf,alpha,Smallest)
    var aspr = a0.copy(); aspr.reduce(surf,alpha,Aspect)
    renr.setDrawColor(255,255,255)
    renr.drawRect(sml.r[0])
    renr.setDrawColor(0,255,0)
    renr.drawRect(aspr.r[0])
    surf.destroy()
  proc drawImage(isurf : SurfacePtr, tw:int, th:int)=
    var ig = newAssetGroup("Input",newRect(0,0,isurf.w,isurf.h))
    var og = newAssetGroup("Output",newRect(0,0,isurf.w,isurf.h))
    renr.doClear()
    var osurf = newSurface(og.rect)
    var r0 = ig.rHorizTiling(tw,th)
    var a1 = newSeq[Asset](0)
    for n0 in 0.. r0.high:
      var asset = newAsset(n0, ig, @[r0[n0]])
      var c = asset.copy()
      c.g = og
      c.r.reduce(c.crop(isurf, alpha, Smallest))
      if not c.r[0].isEmpty(isurf, alpha):
        a1.add(c)
    var a2 = og.packScanline(a1, skipstride, use_speedy).pack
    osurf.copy(isurf, a2)
    renr.copy(osurf, nil, og.rect)
    
  var done = false
  var demo = 0
  proc RunDemo()=
    if demo == 0:
      drawCopy(newAssetGroup("MyGroup", newRect(0,0,256,256)),150, 4, 4, 30, 30)       
    elif demo == 1:
      drawCopy(newAssetGroup("MyGroup", newRect(0,0,512,512)),600, 4, 4, 30, 30)       
    elif demo == 2:
      drawCopy(newAssetGroup("MyGroup", newRect(0,0,512,512)),32*32, 16, 16, 0, 0)       
    elif demo == 3:
      drawCrops(newAssetGroup("MyGroup", newRect(0,0,256,256)))
    elif demo == 4:
      drawImage(surftiles32, 32, 32)
    elif demo == 5:
      drawImage(surftiles16, 16, 16)
    elif demo == 6:
      drawImage(surftiles8, 8, 8)
    elif demo == 7:
      drawImage(surftiles16_2, 16, 16)
    else:
      demo = 0

  var tt = 0'f64
  while not done:
    while pollEvent(evnt):
      if evnt.kind == QuitEvent:
        done = true
      if evnt.kind == KeyDown:
        demo = (demo + 1)
        
    let ct = getTicks();
    RunDemo()
    let lt = getTicks();
    tt = (float(lt-ct) * 0.1 + tt * 0.9)
    echo("frame ms: ",$(lt-ct), " avg: ",$tt)
        
    present(renr)
    delay(1)
    
  destroyWindow(wiow)

  system.quit(0)

test()
display()
