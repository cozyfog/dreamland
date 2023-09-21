@echo off

set BINARY=win32_dreamland.exe
set SOURCE=..\source\*.c
set LIBRARIES=gdi32.lib user32.lib Ole32.lib opengl32.lib glew32.lib
set FLAGS=/nologo /FC /Zi

pushd build
cl %FLAGS% %SOURCE% %LIBRARIES% /I..\extern\ /Fe%BINARY%
popd