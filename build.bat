@echo off

set BINARY=win32_dreamland.exe
:: set SOURCE=..\source\win32_main.c ..\source\dreamland.c ..\source\render.c ..\source\sprite.c ..\source\entity.c
set SOURCE=..\source\*.c
set LIBRARIES=gdi32.lib user32.lib Ole32.lib opengl32.lib glew32.lib

pushd build
cl /nologo /FC /Zi %SOURCE% %LIBRARIES% /I..\extern\ /Fe%BINARY%
popd