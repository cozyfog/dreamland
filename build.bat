@echo off

set BINARY=..\build\win32_dreamland.exe
set SOURCE=..\source\*.c
set LIBRARIES=gdi32.lib user32.lib Ole32.lib opengl32.lib ..\build\glew32.lib
set FLAGS=/nologo /FC /Zi

pushd build-int
cl %FLAGS% %SOURCE% %LIBRARIES% /I..\extern\ /Fe%BINARY%
popd