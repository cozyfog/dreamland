@echo off
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
start devenv build\win32_dreamland.sln
start C:\4coder\4ed.exe project.4coder
exit