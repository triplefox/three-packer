@echo off
cd bin
del example2.exe
del result*.bmp
nim c -p:..\..\packer ..\example2.nim
move ..\example2.exe .
echo **************
echo Running exe...
echo **************
example2.exe
cd ..