@echo off

set MINGW64_BIN=D:\Program Files (x86)\Dev-Cpp\MinGW64\bin
set FFMPEG_BIN=D:\Program Files\ffmpeg-shared\bin

@REM 检测是否含有FFmpeg,需要64位版
echo Checking whether FFMPEG bin is in PATH...
set path_found=""
for %%I in ("%PATH:;=";"%") do (
    @REM echo %%I
    if /i %%I=="%FFMPEG_BIN%" (
        echo OK! We found the %%I
        echo We have FFMPEG bin in PATH...
        set path_found=1
    )
)

@REM 如果路径不存在就设置路径
if /i %path_found%=="" (
    echo There is no FFmpeg in PATH
    echo Add FFMPEG bin to PATH...
    call :SetFFmpeg
)


@REM 设置MinGw64位，为path的第一项
echo Checking whether MINGW64_BIN is the first in PATH...
for /f "tokens=1 delims=;" %%I in ("%PATH%") do (
    echo First is "%%I"
    echo Mingw is "%MINGW64_BIN%"
    if "%%I"=="%MINGW64_BIN%" (
        echo First is MINGW64_BIN,OK!
    ) else (
        echo First is not MINGW64_BIN.......
        echo Add MINGW64_BIN to PATH first...
        call :SetMinGw64 
    )
)


@REM 检查之前是否编译过，编译过，清除啦重编译。
if not exist main.o (
	if not exist main.exe (
        echo There is no make,we can make directly
        make
    ) else (
        echo Opps!There already make before,we should clean first,then make it.
        make clean
        make
    )
) else (
        echo Opps!There already make before,we should clean first,then make it.
        make clean
        make
)

for /F "tokens=1 delims=#" %%a in ('"prompt #$E# & echo on & for %%b in (1) do rem"') do set "ESC=%%a"
set back_color=196
set forward_color=47
echo %esc%[48;5;%forward_color%;38;5;%back_color%mRun the main.exe%esc%[0m
echo %esc%[38;5;%forward_color%m==========================================================%esc%[0m
main.exe
echo.
echo %esc%[38;5;%forward_color%m==========================================================%esc%[0m
pause
goto :eof


@REM 设置PATH中FFmpeg64位路径
:SetFFmpeg
    set path=%FFMPEG_BIN%;%path%
    echo FFmpeg Add OK!
    goto :eof

@REM 设置PATH中Minw64位路径为第一位
:SetMinGw64
    set path=%MINGW64_BIN%;%path%
    echo MinGw64 Add OK!
    goto :eof