@echo off
echo Compiling Reflective Regret Slides

set ROOT=C:\ultra
set gccdir=%ROOT%\gcc
set PATH=%ROOT%\gcc\mipse\bin;%ROOT%\usr\sbin;C:\WINDOWS\system32;
set gccsw=-mips3 -mgp32 -mfp32 -funsigned-char -D_LANGUAGE_C -D_ULTRA64 -D__EXTENSIONS__
set n64align=on
make
set MAKEERROR=%errorlevel%
echo.
goto ErrorCheck


:ErrorCheck
if "%MAKEERROR%"=="2" (
    echo An error occurred during compilation.
    pause
    exit
)
if NOT "%MAINBATCH%"=="1" (
    pause
)