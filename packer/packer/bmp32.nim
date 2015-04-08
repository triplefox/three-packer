import endians
import sdl2
import sdl2.image

discard IMG_Init

proc loadImage*(filename:string):PSurface=
  var suce = IMG_Load(cstring(filename))  
  if suce == nil:
    var err = new Exception
    err.msg = "Failed to load \""&filename&"\": "&($GetError())
    raise err
  return suce

proc writeBMP32(fhdl : File, isurf : PSurface)=

  proc wu8(s0 : seq[uint8]) =
    discard fhdl.writeBytes(cast[seq[int8]](s0), 0, s0.len)  
  proc wi(i0 : int)=
    discard fhdl.writeBytes(cast[seq[int8]](@[
      uint8((i0) and <256),
      ((i0) shr 8) and <256,
      ((i0) shr 16) and <256,
      ((i0) shr 24) and <256,
      ]), 0, 4)  
  proc add(s0 : var seq[uint8], i0 : int) =
      s0.add(@[uint8((i0) and <256),
      ((i0) shr 8) and <256,
      ((i0) shr 16) and <256,
      ((i0) shr 24) and <256,])
  proc bi(i0 : uint32):uint32=
    var p : uint32 = 0
    var q : uint32 = i0
    bigEndian32(addr(p), addr(q))
    return uint32(p)

  var pxformate = MasksToPixelFormatEnum( # RGBA8888
    32, bi(0x0000FF00'u32), bi(0x00FF0000'u32), bi(0xFF000000'u32), bi(0x000000FF'u32))
  var surf = ConvertSurfaceFormat(isurf, pxformate, 0)

  # Get bytes

  type
    I32Data{.unchecked.} = array[0..0, int32]
  var pxdata : ptr I32Data
  pxdata = cast[ptr I32Data](surf.pixels)
  let pxdlen = (surf.pitch * surf.h)

  # Pass in width, height, masks, etc. to DIB

  var dib : seq[uint8] = @[]
  # DIB HEADER
  dib.add(surf.w)
  dib.add(surf.h)
  dib.add(@[0x01'u8,0x00]) # number of color planes
  dib.add(@[surf.format.BitsPerPixel,0x00]) # bits per pixel
  dib.add(@[0x03'u8,0x00,0x00,0x00]) # BI_BITFIELDS
  dib.add(pxdlen) # size of raw bitmap data + padding
  dib.add(@[0x13'u8,0x0B,0x00,0x00]) # horizontal print resolution
  dib.add(@[0x13'u8,0x0B,0x00,0x00]) # vertical print resolution
  dib.add(@[0x00'u8,0x00,0x00,0x00]) # number of colors in palette
  dib.add(@[0x00'u8,0x00,0x00,0x00]) # number of important colors (0 = all)
  dib.add(cast[int](surf.format.Rmask)) # red mask (little-endian)
  dib.add(cast[int](surf.format.Gmask)) # green mask (little-endian)
  dib.add(cast[int](surf.format.Bmask)) # blue mask (little-endian)
  dib.add(cast[int](surf.format.Amask)) # alpha mask (little-endian)
  dib.add(@[0x20'u8,0x6E,0x69,0x57]) # "Win" - LCS_WINDOWS_COLOR_SPACE
  dib.add(@[0x24'u8,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00
    ]) # CIEXYZTRIPLE color space endpoints (unused in "Win")
  dib.add(@[0x00'u8,0x00,0x00,0x00]) # Red gamma (unused in "Win")
  dib.add(@[0x00'u8,0x00,0x00,0x00]) # Green gamma (unused in "Win")
  dib.add(@[0x00'u8,0x00,0x00,0x00]) # Blue gamma (unused in "Win")

  # BMP HEADER
  var bmp : seq[uint8] = @[]
  bmp.add(@[0x42'u8,0x4D]) # BM
  bmp.add(14 + dib.len + pxdlen) # size
  bmp.add(@[0x00'u8,0x00]) # unused
  bmp.add(@[0x00'u8,0x00]) # unused
  bmp.add(@[0x7A'u8,0x00,0x00,0x00]) # Pixel array offset

  wu8(bmp)
  wi(dib.len + 4)
  wu8(dib)
  # write in bottom to top order
  for i0 in 0.. (<surf.h):
    let pt0 = surf.pixels
    let i1 = (<surf.h) - i0
    let pt1 = int(surf.pitch * i1)
    if (pt1 + <surf.pitch < pxdlen):
      discard fhdl.writeBuffer(cast[pointer](cast[int](pt0) + pt1), surf.pitch)
  surf.destroy()

var outf = open("result.bmp", fmWrite)
outf.writeBMP32(loadImage("goodresult.bmp"))
outf.close()
outf = open("result2.bmp", fmWrite)
outf.writeBMP32(loadImage("jerom-fantasy-tileset.png"))
outf.close()
