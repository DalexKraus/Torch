echo off
setlocal ENABLEDELAYEDEXPANSION
set files=
for /f %%i in ('dir /b /a-d ..\imgui') do (
    set files=!files! "%%i"
)
echo %files%
echo on
pause