set PLATFORM=%1
if "%PLATFORM%"=="" set PLATFORM=x64
set PLATFORM_PREFIX=
if "%PLATFORM%"=="x64" set PLATFORM_PREFIX=-x64
set _CL_=/utf-8
set PATH=c:\Python37%PLATFORM_PREFIX%;c:\Program Files\Git\usr\bin;c:\MinGW\bin;%PATH%
set ROOT_DIR=%~dp0\..\

mkdir build
cd build
cmake .. -A %PLATFORM%
cmake --build . --config Release
ctest -C Release
cd python

rem https://www.appveyor.com/docs/windows-images-software/#python
call :BuildPython C:\Python35%PLATFORM_PREFIX%
call :BuildPython C:\Python36%PLATFORM_PREFIX%
call :BuildPython C:\Python37%PLATFORM_PREFIX%

:BuildPython
%1\python -m pip install -r %ROOT_DIR%\python\requirements-dev.txt
%1\python %ROOT_DIR%\python\setup.py test bdist_wheel
rmdir /Q /S build
del /S *.pyd
exit /b

cd ..