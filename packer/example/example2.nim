import json
import sdl2
import sdl2.image
import pack
import packsdl
import bmpsdl
import algorithm
import strutils
import tables
import packsdleasy
discard image.init

# in this example, we load each of these images as tiles,
# and then pack them all into one group.
# The result is saved as a series of 256x256 images and JSON.

var isurf32 = loadImage("jerom-fantasy-tileset-32.png");
var ig32 = newAssetGroup("Input32",newRect(0,0,isurf32.w,isurf32.h))
var isurf16 = loadImage("jerom-fantasy-tileset-16.png");
var ig16 = newAssetGroup("Input16",newRect(0,0,isurf16.w,isurf16.h))
var isurf8 = loadImage("jerom-fantasy-tileset-8.png");
var ig8 = newAssetGroup("Input8",newRect(0,0,isurf8.w,isurf8.h))
var og = newAssetGroup("Output",newRect(0,0,256,256))

var bd = newBundle(@[
            getTiles(ig32,isurf32,32,32),
            getTiles(ig16,isurf16,16,16),
            getTiles(ig8,isurf8,8,8)],
            @[ig32,ig16,ig8],
            @[isurf32,isurf16,isurf8])
#echo(packSheet(isurf32, og, osurf, getTiles(ig32, isurf32, 32, 32)))

var ct = 0
for tup in packBundle(bd, og):  
  let fname = "result"&intToStr(ct, 4)&".bmp"
  echo(fname)
  echo(getPixelFormatName(tup.surf.format.format))
  var outf = open(fname, fmWrite)
  outf.writeBMP32(tup.surf)
  outf.close()
  var j = saveJSON(tup.sb.asset, fname).json
  echo(loadJSON(j).asset)
  ct += 1  
