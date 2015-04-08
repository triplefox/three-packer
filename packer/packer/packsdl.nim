import sdl2
import pack
import math

type
  CroppingType* = enum
    Smallest, # Reduce to the smallest size
    Aspect, # Crop evenly on each side(e.g. preserve non-center offsetting)   
    AspectV, # Crop horizontally smallest, vertical even    
    AspectH, # Crop vertically smallest, horizontally even   
    Preserve # Keep all pixels
  SheetBundle* = ref object # concatenated sheets for repacking: 
    # group id is used to link the asset to its origin surface. 
    asset* : seq[Asset]
    group* : seq[AssetGroup]
    surf* : seq[SurfacePtr]

proc newSDLRect*(r : pack.Rect):sdl2.Rect=
  (x:cint(r.x), y:cint(r.y), w:cint(r.w), h:cint(r.h))
proc newSDLRect*(x:int, y:int, w:int, h:int):sdl2.Rect=
  (x:cint(x), y:cint(y), w:cint(w), h:cint(h))
converter SDLRect*(r: pack.Rect):sdl2.Rect = return newSDLRect(r)
proc fillRect*(renr:RendererPtr,x:int,y:int,w:int,h:int)=
  var rect0 = newSDLRect(x,y,w,h)
  renr.fillRect(addr(rect0))
proc fillRect*(renr:RendererPtr,r:pack.Rect)=
  var rect0 = SDLRect(r)
  renr.fillRect(addr(rect0))
proc drawRect*(renr:RendererPtr,x:int,y:int,w:int,h:int)=
  var rect0 = newSDLRect(x,y,w,h)
  renr.drawRect(rect0)
proc drawRect*(renr:RendererPtr,r:pack.Rect)=
  var rect0 = SDLRect(r)
  renr.drawRect(rect0)
proc drawCorners*(renr:RendererPtr,x:int,y:int,w:int,h:int)=
  renr.drawPoint(cint(x), cint(y))
  renr.drawPoint(cint(x+(<w)), cint(y))
  renr.drawPoint(cint(x), cint(y+(<h)))
  renr.drawPoint(cint(x+(<w)), cint(y+(<h)))
proc newTestAsset*(g,x,y,w,h):Asset=
  newAsset(0, g, @[newRect(x,y,w,h,
    @[newData("Color",math.random(int.high))])]);
proc newTestAsset*(g,x,y,w,h,c):Asset=
  newAsset(0, g, @[newRect(x,y,w,h,
    @[newData("Color",c)])]);
proc drawColors*(renr : RendererPtr, a0:seq[Asset])=
  for i0 in 0.. a0.high:
    let r = a0[i0].r[0]
    let ci = r.d["Color"]
    let c = (if ci.len > 0: ci[0].v else: 0xFFFFFF)
    setDrawColor(renr, uint8((c shr sizeof(int)*2) and <256), 
      uint8((c shr sizeof(int)) and <256), uint8((c) and <256), 255);
    renr.fillRect(r.x,r.y,r.w,r.h)
    setDrawColor(renr, 255, 255, 255, 255);
    renr.drawCorners(r.x,r.y,r.w,r.h)
proc drawColors*(surf : SurfacePtr, a0:seq[Asset])=
  var swrenr = createSoftwareRenderer(surf)  
  swrenr.drawColors(a0)
  swrenr.destroy()
proc newSurface*(w, h, format):SurfacePtr=
  var fmt = allocFormat(format)
  result = createRGBSurface(0, cint(w), cint(h), 
    cint(fmt.BitsPerPixel), fmt.RMask, fmt.GMask, fmt.BMask, fmt.AMask)
  fmt.destroy()    
proc newSurface*(w, h):SurfacePtr=
  return newSurface(w, h, masksToPixelFormatEnum(
    32, uint32(0xFF000000), uint32(0x00FF0000), 
        uint32(0x0000FF00), uint32(0x000000FF))) # RGBA888
proc newSurface*(rect:pack.Rect):SurfacePtr=newSurface(rect.w, rect.h)
proc copy*(renr : RendererPtr, src : SurfacePtr, srcrect : ptr sdl2.Rect, destrect : ptr sdl2.Rect)=
  var tx = renr.createTextureFromSurface(src)
  renr.copy(tx, srcrect, destrect)
  tx.destroy()
proc copy*(renr : RendererPtr, src : SurfacePtr, srcrect : pack.Rect, destrect : pack.Rect)=
  if (srcrect.w != destrect.w or srcrect.h != destrect.h):
    var ex = new(Exception)
    ex.msg = "Source asset dimensions are different from dest asset dimensions: " &
      $(srcrect.w) & "x" & $(srcrect.h) & " " &
      $(destrect.w) & "x" & $(destrect.h) & " "
    raise ex
  var r0 = SDLRect(srcrect); var r1 = SDLRect(destrect)
  renr.copy(src, addr(r0), addr(r1))
proc copy*(renr : RendererPtr, src : SurfacePtr, srcrect : ptr sdl2.Rect, destrect : pack.Rect)=
  var r1 = SDLRect(destrect)
  renr.copy(src, srcrect, addr(r1))
proc copy*(renr : RendererPtr, src : SurfacePtr, srcrect : pack.Rect, destrect : ptr sdl2.Rect)=
  var r0 = SDLRect(srcrect)
  renr.copy(src, addr(r0), destrect)
proc copy*(renr:RendererPtr,src:SurfacePtr,a0:Asset,a1:Asset)=
  var rect0 : sdl2.Rect = SDLRect(a0.r[0])
  var rect1 : sdl2.Rect = SDLRect(a1.r[0])
  renr.copy(src,addr(rect0),addr(rect1))
#copy (two sequence) - copy each asset of sequence a0 to the corresponding one in a1 
proc copy*(renr:RendererPtr,src:SurfacePtr,a0:seq[Asset],a1:seq[Asset])=
  if (a0.len != a1.len):
    var ex = new(Exception)
    ex.msg = "Source asset sequence is different size from dest asset sequence"
    raise ex
  var rect0 : sdl2.Rect
  var rect1 : sdl2.Rect
  var tx = renr.createTextureFromSurface(src)
  for i0 in 0.. a0.high:
    rect0 = SDLRect(a0[i0].r[0])
    rect1 = SDLRect(a1[i0].r[0])
    if (rect0.w != rect1.w or rect0.h != rect1.h):
      var ex = new(Exception)
      ex.msg = "Source asset dimensions are different from dest asset dimensions"
      raise ex
    renr.copy(tx, addr(rect0), addr(rect1))
  tx.destroy()
#copy (one sequence) - map the "previous" field of each asset to the current one.
proc copy*(renr:RendererPtr,src:SurfacePtr,a0:seq[Asset])=
  var rect0 : sdl2.Rect
  var rect1 : sdl2.Rect
  var tx = renr.createTextureFromSurface(src)
  for a1 in a0:
    rect0 = SDLRect(a1.p.r[0])
    rect1 = SDLRect(a1.r[0])
    if (rect0.w != rect1.w or rect0.h != rect1.h):
      var ex = new(Exception)
      ex.msg = "Source asset dimensions are different from dest asset dimensions"
      raise ex
    renr.copy(tx, addr(rect0), addr(rect1))
  tx.destroy()
proc copy*(renr:RendererPtr,sbd:SheetBundle)=
  for a0 in sbd.asset:
    renr.copy(sbd.surf[a0.p.g.id], sbd.asset)
proc copy*(dest:SurfacePtr,src:SurfacePtr,a0:seq[Asset])=
  var renr = createSoftwareRenderer(dest)
  copy(renr, src, a0)
  renr.destroy()
proc copy*(dest:SurfacePtr,sbd:SheetBundle)=
  var renr = createSoftwareRenderer(dest)
  copy(renr, sbd)
  renr.destroy()
# cropBounds: masks against a surface color key to find keepworthy rectangle
# Make sure your key is appropriate for the surface pixel format!
proc cropBounds*(surf:SurfacePtr,colorkey:uint32,r:pack.Rect):CropResult=
  var bottom = min(r.y, <surf.h)
  var right = min(r.x, <surf.w)
  var top = max(r.y + <r.h, 0)
  var left = max(r.x + <r.w, 0)
  for y0 in r.y.. <r.y+r.h:
    for x0 in r.x.. <r.x+r.w:
      var p0 : int = int(x0 * int(surf.format.BytesPerPixel) + 
        int(y0 * surf.pitch))
      let px = cast[ptr uint32](cast[int](surf.pixels)+p0)[]
      let maskresult = colorkey and px
      if maskresult != uint32(0):
        top = min(y0, top)
        left = min(x0, left)
        bottom = max(y0, bottom)
        right = max(x0, right)
  if bottom < top:
    swap(top, bottom)
  if right < left:
    swap(left, right)
  return newCropResult(left-r.x,top-r.y,(r.x+(<r.w))-right,(r.y+(<r.h))-bottom)
proc crop*(asset : Asset, surf:SurfacePtr, colorkey:uint32, cropt:CroppingType):CropResult=
  if cropt == Preserve:
    return newCropResult(0,0,0,0)
  elif cropt == Smallest:
    var e = cropBounds(surf, colorkey, asset.r[0])
    return e
  elif cropt == Aspect:
    var b = cropBounds(surf, colorkey, asset.r[0])
    let sz = min(b.left,b.right,b.top,b.bottom)
    return newCropResult(sz, sz, sz, sz)
  elif cropt == AspectV:
    var b = cropBounds(surf, colorkey, asset.r[0])
    let sz = min(b.top,b.bottom)
    return newCropResult(b.left, sz, b.right, sz)
  elif cropt == AspectH:
    var b = cropBounds(surf, colorkey, asset.r[0])
    let sz = min(b.left,b.right)
    return newCropResult(sz, b.top, sz, b.bottom)
proc isEmpty*(rect : pack.Rect, surf:SurfacePtr, colorkey:uint32):bool=
  for y0 in rect.y.. <rect.y+rect.h:
    for x0 in rect.x.. <rect.x+rect.w:
      var p0 : int = int(x0 * int(surf.format.BytesPerPixel) + 
        int(y0 * surf.pitch))
      let px = cast[ptr uint32](cast[int](surf.pixels)+p0)[]
      let maskresult = colorkey and px
      if maskresult > uint32(0):
        return false
  return true
proc isEmpty*(asset : Asset, surf:SurfacePtr, colorkey:uint32):bool=
  isEmpty(asset.r[0], surf, colorkey)
proc reduce*(asset : Asset, isurf : SurfacePtr, colorkey:uint32, cropt:CroppingType)=
  asset.r.reduce(asset.crop(isurf, colorkey, cropt))
proc newBundle*(asa : seq[seq[Asset]], 
  gra : seq[AssetGroup], 
  surfa : seq[SurfacePtr]):SheetBundle=
  new(result)
  result.asset = @[]
  result.group = @[]
  result.surf = @[]
  var gid = 0 
  for g0 in gra:
    g0.id = gid
    gid += 1
    result.group.add(g0)
  var aid = asa[0][0].i 
  for s0 in asa:
    for a0 in s0:
      a0.i = aid; aid+=1
      result.asset.add(a0)
  for s1 in surfa:
    result.surf.add(s1)