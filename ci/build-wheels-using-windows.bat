set PLATFORM=%1
if "%PLATFORM%"=="" set PLATFORM=x64
set PLATFORM_PREFIX=
if "%PLATFORM%"=="x64" set PLATFORM_PREFIX=-x64
set _CL_=/utf-8
set PATH=c:\Python37%PLATFORM_PREFIX%;c:\Program Files\Git\usr\bin;c:\MinGW\bin;%PATH%

mkdir build
cd build
cmake ..
cmake --build . --config Release