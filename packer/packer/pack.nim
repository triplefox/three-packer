import sequtils
import algorithm

type
  DataEntry* = object
    k*:string # key
    v*:int # value
  Rect* = object
    x*:int
    y*:int
    w*:int # width
    h*:int # height
    d*:seq[DataEntry] # metadata: stored as seq, behaves like OrderedTable.
  AssetGroup* = ref object
    rect*:Rect # describes surface that assets are packed on
    name*:string
    counter*:int # start point for auto-incrementing ids
    id*:int # unique identifier (e.g. index of bitmap)
  Asset* = ref object
    p*:Asset # previous version of asset
    i*:int # asset id
    g*:AssetGroup # group association
    r*:seq[Rect] # rectangles: 1st is boundary. 
                # additional are metadata, relative to top-left.
  CropResult* = ref object
    left*:int
    right*:int
    top*:int
    bottom*:int

proc newAsset*(i:int, g:AssetGroup, r:seq[Rect]):Asset=
  new(result); let rs = result
  rs.i = i; rs.g = g; rs.r = r;

proc copy*(a : Asset):Asset=
  new(result); result.p = a; result.i = a.i; result.g = a.g; 
  result.r = a.r

proc `$`*(d : DataEntry):string=($d.k)&"="&($d.v)
proc `$`*(r : Rect):string="x:"&($r.x)&" y:"&($r.y)&" w:"&($r.w)&" h:"&($r.h)&
  (if r.d != nil: (" d:"&($r.d)) else: "")
proc `$`*(c : CropResult):string="l:"&($c.left)&" t:"&($c.top)&
  " r:"&($c.right)&" b:"&($c.bottom)
  
proc `$`*(g : AssetGroup):string=($g.name&"="&($g.counter)&
  " w:"&($g.rect.w)&" h:"&($g.rect.h))
proc `$`*(p : Asset):string=("id:"&($p.i)&" group:"&($p.g.name)&" rect:"&($p.r))

type
  AssetRectFilter* = proc(r : Rect ):bool
  AssetRectView* = object
    a*:Asset
    i*:int

# viewAssetRects: Creates asset-relative indexes of rectangles from a filtering function.
# (This lets us mutate them without copies)
proc viewAssetRects*(ar:seq[Asset], fn: AssetRectFilter):seq[AssetRectView]=
  result = @[]
  for a in ar:
    for i0 in 0..a.r.high:
      if fn(a.r[i0]):
        var v : AssetRectView
        v.a = a
        v.i = i0
        result.add(v)

proc newAssetGroup*(name, rect):AssetGroup=
  new(result); result.name = name; result.rect = rect; result.counter = 0
proc newAssetGroup*(rect):AssetGroup=
  new(result); result.name = "Untitled"; result.rect = rect; result.counter = 0

proc newRect*(x:int,y:int,w:int,h:int,d:seq[DataEntry]=nil):Rect=
  result.x=x; result.y=y; result.w=w; result.h=h; result.d=d

proc newCropResult*(left,top,right,bottom):CropResult=
  new(result); result.left = left; result.right = right
  result.top = top; result.bottom = bottom

#add: push a new data entry into the DataEntry sequence.
proc add*(s : var seq[DataEntry], k : string, v : int)=
  var d : DataEntry; d.k = k; d.v = v; s.add(d)

# []=: write this data as a unique key in the DataEntry sequence.
proc `[]=`*(s : var seq[DataEntry], k : string, v : int)=
  s.keepItIf(it.k!=k); s.add(k, v)

# []: get all instances of this key in the DataEntry sequence
proc `[]`*(s : seq[DataEntry], k : string):seq[DataEntry]=s.filterIt(it.k==k)

proc newData*(k : string, v : int):DataEntry= 
  result.k = k; result.v = v;

#rHorizTiling: given an assetgroup g and tile width and height
#turn the tiles running left to right, top to bottom into rect objects.
#Optional increment values and starting positions are provided to customize
#the tiling behavior(e.g. right to left, bottom to top, add margins, etc.)
proc rHorizTiling*(g : AssetGroup, tw : int, th : int, 
  iw : int = 0, ih : int = 0, sx : int=0, sy : int=0):seq[Rect]=
  var y0 = sy
  var i0 = 0
  var iw0 = (if iw == 0: (tw) else: (iw))
  var ih0 = (if ih == 0: (th) else: (ih))
  result = @[]
  while y0 + th <= g.rect.h and y0 >= 0:
    var x0 = sx
    while x0 + tw <= g.rect.w and x0 >= 0:
      result.add(@[newRect(x0,y0,tw,th)])
      x0 += iw0
      i0 += 1
    y0 += ih0

#rVertTiling: given an assetgroup g and tile width and height
#turn the tiles running top to bottom, left to right into rect objects.
#Optional increment values and starting positions are provided to customize
#the tiling behavior(e.g. right to left, bottom to top, add margins, etc.)
proc rVertTiling*(g : AssetGroup, tw : int, th : int, 
  iw : int = 0, ih : int = 0, sx : int=0, sy : int=0):seq[Rect]=
  var x0 = sx
  var i0 = 0
  var iw0 = (if iw == 0: (tw) else: (iw))
  var ih0 = (if ih == 0: (th) else: (ih))
  result = @[]
  while x0 + tw <= g.rect.w and x0 >= 0:
    var y0 = sy
    while y0 + th <= g.rect.h and y0 >= 0:
      result.add(@[newRect(x0,y0,tw,th)])
      y0 += ih0
      i0 += 1
    x0 += iw0

#rWidths: given an assetgroup g, a set of widths, and a height,
#turn the tiles running left to right, top to bottom into rect objects.
#The height of each row and start offset is adjustable like rHorizTiling.
#When posiw is false, widths run right to left.
proc rWidths*(g : AssetGroup, widths : seq[int], th : int, 
  posiw : bool = true, ih : int = 0, sx : int=0, sy : int=0):seq[Rect]=
  var y0 = sy
  var i0 = 0
  var ih0 = (if ih == 0: (th) else: (ih))
  result = @[]
  while i0 < len(widths) and y0 + th <= g.rect.h and y0 >= 0:
    var x0 = sx
    while i0 < len(widths) and x0 + widths[i0] <= g.rect.w and x0 >= 0:
      result.add(@[newRect(x0,y0,widths[i0],th)])
      if posiw: x0 += widths[i0]  else: x0 -= widths[i0]
      i0 += 1
    y0 += ih0

#rHeights: given an assetgroup g, a set of heights, and a width,
#turn the tiles running top to bottom, left to right into rect objects.
#The height of each row and start offset is adjustable like rHorizTiling.
#When posih is false, heights run bottom to top.
proc rHeights*(g : AssetGroup, heights : seq[int], tw : int, 
  posih : bool = true, iw : int = 0, sx : int=0, sy : int=0):seq[Rect]=
  var x0 = sx
  var i0 = 0
  var iw0 = (if iw == 0: (tw) else: (iw))
  result = @[]
  while i0 < len(heights) and x0 + tw <= g.rect.w and x0 >= 0:
    var y0 = sy
    while i0 < len(heights) and y0 + heights[i0] <= g.rect.h and y0 >= 0:
      result.add(@[newRect(x0,y0,tw,heights[i0])])
      if posih: y0 += heights[i0]  else: y0 -= heights[i0]
      i0 += 1
    x0 += iw0

#assetsOfRects: given an assetgroup g, a set of rects(x/y and width/height),
#turn the tiles into new assets in the given order.
proc assetsOfRects*(g : AssetGroup, rects : seq[array[4,int]]):seq[Asset]=
  var i0 = 0
  result = @[]
  while i0 < len(rects):
    let x0 = rects[i0][0]
    let y0 = rects[i0][1]
    let w0 = rects[i0][2]
    let h0 = rects[i0][3]
    result.add(newAsset(g.counter+i0, g, @[newRect(x0,y0,w0,h0)]))
    i0 += 1
proc assetsOfRects*(g : AssetGroup, rects : seq[int]):seq[Asset]=
  var i0 = 0
  result = @[]
  while i0 * 4 + 3 <= len(rects):
    let x0 = rects[i0*4+0]
    let y0 = rects[i0*4+1]
    let w0 = rects[i0*4+2]
    let h0 = rects[i0*4+3]
    result.add(newAsset(g.counter+i0, g, @[newRect(x0,y0,w0,h0)]))
    i0 += 1
proc assetsOfRects*(g : AssetGroup, rects : seq[Rect]):seq[Asset]=
  var i0 = 0
  result = @[]
  while i0 < len(rects):
    result.add(newAsset(g.counter+i0, g, @[rects[i0]]))
    i0 += 1

proc minSizeOfAssets*(assets : seq[Asset], tw:int=0, th:int=0):array[2,int]=
  var tw0=tw; var th0=th; 
  for a in assets:
    tw0 = max(a.r[0].w, tw0)
    th0 = max(a.r[0].w, th0)
  return [tw0,th0]
proc totalAreaOfAssets*(assets : seq[Asset]):int=
  var area = 0 
  for a in assets:
    area += (a.r[0].w * a.r[0].h)
  return area
# overpacked? discard at least one asset, starting from the end of the sequence
proc discardAssets*(assets : var seq[Asset], minarea :int):seq[Asset]=
  var area = totalAreaOfAssets(assets)
  result = newSeq[Asset](0)
  if area > minarea:
    while area > minarea:
      let ap = assets.pop()
      area -= ap.r[0].w * ap.r[0].h
      result.add(ap)
  else: # just one
    result.add(assets.pop())
  

#reduce: reduce the first rectangle by each side(left,top,right,bottom), 
#then translate all other rectangles relative to the new top-left position.
proc reduce*(r : var seq[Rect], lt : int, tp : int, rt : int, bm : int)=
  if r.len > 0: # crop the boundary rect
    r[0].x += lt; r[0].y += tp; r[0].w -= lt + rt; r[0].h -= tp + bm;
    if r.len > 1: # translate metadata rects
      for i0 in 1.. high(r):
        r[i0].x -= lt; r[i0].y -= tp
proc reduce*(r : var seq[Rect], cropr : CropResult)=
  reduce(r, cropr.left, cropr.top, cropr.right, cropr.bottom)

proc fitsInTileSize*(rects : seq[Rect], w0 : int, h0 : int):seq[Rect]=
  result = @[]
  for r0 in rects:
    if r0.w > w0 or r0.h > h0:
      result.add(r0)
proc fitsInTileSize*(assets : seq[Asset], w0 : int, h0 : int):seq[Asset]=
  result = @[]
  for a0 in assets:
    if a0.r[0].w > w0 or a0.r[0].h > h0:
      result.add(a0)
  
# Moves each asset's boundary to the TL position of the corresponding rects. 
proc packToRectsTL*(g : AssetGroup, assets : seq[Asset], rects : seq[Rect]):
  seq[Asset]=
  result = @[]
  for i0 in 0..assets.high:
    var a = copy assets[i0]
    a.r[0].x = rects[i0].x
    a.r[0].y = rects[i0].y
    result.add(a)
# Moves each asset's boundary to the center of the corresponding rects. 
proc packToRectsC*(g : AssetGroup, assets : seq[Asset], rects : seq[Rect]):
  seq[Asset]=
  result = @[]
  for i0 in 0..assets.high:
    var a = copy assets[i0]
    a.r[0].x = rects[i0].x + int(rects[i0].w/2) - int(a.r[0].w/2)
    a.r[0].y = rects[i0].y + int(rects[i0].h/2) - int(a.r[0].h/2)
    result.add(a)
# Moves each asset's boundary to the center of the corresponding rects and
# grows the boundary to fit. Asset prev contains the "pre-growth" boundary.
proc packToRectsGrowC*(g : AssetGroup, assets : seq[Asset], rects : seq[Rect]):
  seq[Asset]=
  result = @[]
  for i0 in 0..assets.high:
    var a = copy assets[i0]
    let r0 = rects[i0]
    a.r[0].x = r0.x + int(r0.w/2) - int(a.r[0].w/2)
    a.r[0].y = r0.y + int(r0.h/2) - int(a.r[0].h/2)
    a = copy a
    let lt = r0.x-a.r[0].x
    let tp = r0.y-a.r[0].y
    let rt = (a.r[0].x + a.r[0].w)-(r0.x + r0.w)
    let bm = (a.r[0].y + a.r[0].h)-(r0.y + r0.h)
    reduce(a.r, lt, tp, rt, bm)
    result.add(a)

proc aabb*(x0,y0,w0,h0,x1,y1,w1,h1):bool=
  not ((x0 + w0 <= x1) or (x0 >= x1 + w1) or (y0 + h0 <= y1) or (y0 >= y1 + h1))

type
  PackException* = object of Exception
    id*: int # id of failing rectangle  
  PackManifest* = ref object
    pack*: seq[Asset]
    remainder*: seq[Asset]



# PackScanline: Sorts the assets from largest to smallest.
# Then packs them by looking at each scanline, left to right, top to bottom,
# and picking the first available space. Fails if any rectangle can't be packed.
# "skipstride" tells the search to increment every "n" scanlines, more is faster/lower-quality.
# "speedy" uses a less exhaustive search to cull skips faster(usually 2x speed)
# "sort" = false disables the sort.
proc packScanline*(g : AssetGroup, assets : seq[Asset], skipstride=1, speedy=false, sort=true):PackManifest=
  new(result) 
  var pack = newSeq[Asset](assets.len)
  for i0 in 0.. assets.high:
    pack[i0] = assets[i0].copy()
  # initial sort of asset boundaries
  proc whsorter(a,b : Asset):int=
    result = cmp(a.r[0].w * a.r[0].h, b.r[0].w * b.r[0].h)
    if result == 0:
      result = cmp(a.r[0].h, b.r[0].h)
  if sort:
    pack.sort(whsorter, SortOrder.Descending)

  let bw = g.rect.w
  let bh = g.rect.h

  var vstride = pack[0].r[0].h 
  
  discard """
  We use a bitmap to mark off used areas - 
  If you have fewer and larger rectangles, AABBs using a broadphase collision 
  algorithm _might_ be a faster way of doing the same, but it would take
  some care.

  Rewriting this algorithm with a packed bitarray does not seem to help performance:
  the bitarray code is more branchy, negating the fast iteration.

  One of the possible bottlenecks right now is skiplist management. The binary search is quite
  fast, but insert and removal time may be deadly in the larger cases.
  A tree-based structure might serve them better.
  Skips might also be expanded to measure a per-skip border, independently on x and y axis.
  This would allow the skip selection to look for sufficient border size before checking the map.
  (maybe no real gains?) 
  """ 
  var bitmap = newSeq[int8](bw*bh+1)
  var clearzone = newSeq[int8](bw+1)
  var fillzone = clearzone
  for i0 in 0.. fillzone.high:
    fillzone[i0] = 1
  var frontierx = 0
  var frontiery = 0
  var skips = newseq[int](bh)# skiplist
  var i0 = 0
  while i0 < bh:
    skips[i0]=(i0 * bw) # initialize with (0,0)..(0,<bh)
    i0 += skipstride
  for r0 in 0.. pack.high:
    var nextskips : seq[int] = @[] # double buffer
    var x1 = 0
    var y1 = 0
    let cw = pack[r0].r[0].w 
    let ch = pack[r0].r[0].h 
    # search for free points using the skiplist
    var s0 = 0
    block CanFit:
      if cw == 0 or ch == 0: 
        break
      while s0 < skips.len:
        x1 = skips[s0] mod bw
        y1 = int(skips[s0]/bw)
        # falls over container width or height?
        if x1+(<cw) > (<bw) or y1+(<ch) > (<bh):
          s0 += 1
        # overlaps a placed rectangle?
        else:
          # walk through the bitmap
          block Bitmapcheck:
            # use the frontiers to reduce required search space if possible
            let right = (if frontierx <= <x1: max(x1, frontierx) else: <x1 + cw)
            let bottom = (if frontiery <= <y1: max(y1, frontiery) else: <y1 + ch)
            if ((bitmap[right + y1 * bw]) or 
                (bitmap[x1 + bottom * bw]) or 
                (bitmap[right + bottom * bw])) != 0: # early out TL, BL, BR
              s0 += 1
              break Bitmapcheck
            # calculate positions for the top and bottom
            let p1 = y1 * bw
            let p2 = bottom * bw
            # check the _borders_ of the rectangle.
            # top
            let ex0 = equalMem(addr(bitmap[x1+p1]), addr(clearzone[0]), (right-x1)*sizeof(int8)) 
            # bottom
            let ex1 = equalMem(addr(bitmap[x1+p2]), addr(clearzone[0]), (right-x1)*sizeof(int8)) 
            var chk = ex0 and ex1
            # left and right
            let yib = int((bottom - y1)/vstride)
            for y2 in 0.. yib:
              let incr = ((y1+y2*vstride)*bw)
              chk = chk and not cast[bool](bitmap[x1+incr] or bitmap[right+incr])  
              # we can guarantee that nothing overlaps within the area of the vstride,
              # allowing us to iterate down the columns a little faster.
              # this formulation of the loop seems a little faster when benchmarked.              
            if chk: # passed
              break CanFit
            else: # hit
              s0 += 1
              break Bitmapcheck
      result.remainder = pack[r0.. pack.high]
      result.pack = (if r0 > 0: pack[0.. <r0] else: @[])
      return
    # success
    pack[r0].r[0].x = x1; pack[r0].r[0].y = y1
    vstride = min(vstride, pack[r0].r[0].h)
    frontierx = max(frontierx, x1 + cw)
    frontiery = max(frontiery, y1 + ch)
    # fill rectangle and create skips
    var y2 = y1
    while y2 < y1+ch: # right-side skips
      # add skip (if not past border)
      let p0 = y2 * bw
      let skipx = x1+(<cw)+1 
      if (skipx < bw):
        let v = skipx + p0
        # insert in pre-sorted position
        skips.insert(v, skips.lowerBound(v))
      y2 += skipstride
    for y2 in y1.. <y1+ch:
      let p0 = y2 * bw
      # fill row
      copyMem(addr(bitmap[x1+p0]), addr(fillzone[0]), (cw)*sizeof(int8))
    # clear old skips and return new ones in nextskip buffer
    # "speedy" assumes that anything we failed in the previous rect is no good.
    if speedy:
      skips = skips[s0 + 1 .. skips.high]
    else:
      var i0 = 0
      while i0 < skips.len:
        if bitmap[skips[i0]]==0:
          nextskips.add(skips[i0])
        i0+=1
      skips = nextskips
  result.pack = pack

# pack the group and assets into one or more pages of sheets, returned as a sequence of sequences.
proc multipackScanline*(g : AssetGroup, assets : seq[Asset], skipstride=1, speedy=false, sort=true):seq[seq[Asset]]=
  result = @[]
  var manifest = g.packScanline(assets, skipstride, speedy, sort)
  result = result & manifest.pack
  var count = manifest.pack.len
  while manifest.remainder != nil:
    manifest = g.packScanline(manifest.remainder, skipstride, speedy, sort)
    if manifest.pack.len == 0:
      var ex = new Exception
      ex.msg = "Asset too large: "&($manifest.remainder[0])
      raise ex
    result = result & manifest.pack
    count += manifest.pack.len
