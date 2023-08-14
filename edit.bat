@echo off
start devenv build\win32_dreamland.sln
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars64.bat"
start C:\4coder\4ed.exe project.4coder
exit