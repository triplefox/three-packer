@echo off
cd bin
del example1.exe
nim c -p:..\..\packer -d:release ..\example1.nim
move ..\example1.exe .
echo **************
echo Running exe...
echo **************
example1.exe test000.png
cd ..