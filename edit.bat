@echo off
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
start devenv dreamland.sln
start C:\Dependencies\4coder\4ed.exe project.4coder
exit