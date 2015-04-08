three-packer

* What This Is For

Packing source art assets into efficient atlases

Repositioning existing source assets into different forms

Creating and manipulating metadata for assets

There are three .nim files that make up the core of the library, which make progressively more assumptions. There is an additional file for saving BMP.

* What's In It

pack.nim contains the core data structures and the packing algorithms.

packsdl.nim contains loading, display, and rectangle cropping for assets using SDL, and a "sheet bundle" structure that synchronizes the SDL texture data and the atlas data.

packsdleasy.nim contains convenience functions for working with the SDL data in common situations, including tiling, packing, and JSON serialized atlas data.

bmpsdl.nim contains a serializer for BMP32 using SDL surfaces.

Right now the library is only really tested with BMP32 BGRA assets. sdl_image allows loading additional formats, however only the BMP serializer is known to work for saving.

* How to Use It

The suggested usage is to copy the examples and start modifying them to fit your workflow. This is a library intended for making quick, handy scripts that fix up your pipeline problems.

* The Examples

There are two examples included, with build .bat files for Windows:

Example 1 shows the packing functionality in a real-time demo. Press the any key to advance through the demos.

Example 2 takes a source sheet and emits packed assets as .BMP files, and also emits JSON data to the console.

* JSON format description:

dataentry:
    {"k":string, "v":int}
Key-Value data.    
    
rectdata:
    [left, top, width, height, [dataentry]]
Rectangle data.
    
assetdata:
    {"i":int, "g":int, "r":[<rectdata>]}
i: unique id for asset
g: group id
r: rectangles. the first rectangle describes the atlas position; later rectangles are taken to be relative to the first by the processing algorithms.
    
groupdata:
    {"rect":[<rectdata>],"name":string,"counter":int,"id":int}, ...
rect: first rect describes the size of the texture, later rects are user data.
name: human identifier of group
id: unique id for group
    
top level:
    "group": [<groupdata>]
    "asset": [<assetdata>]
list of groups, list of assets
