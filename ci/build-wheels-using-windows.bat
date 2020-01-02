set PLATFORM=%1
if "%PLATFORM%"=="" set PLATFORM=x64
rem see https://www.appveyor.com/docs/appveyor-yml/
rem see https://cmake.org/cmake/help/git-master/generator/Visual%20Studio%2016%202019.html
if "%PLATFORM%"=="x86" set PLATFORM=Win32
set PLATFORM_PREFIX=
if "%PLATFORM%"=="x64" set PLATFORM_PREFIX=-x64
set PROGRAM_FILES_PREFIX=
if "%PLATFORM"=="Win32" set PROGRAM_FILES_PREFIX=" (x86)"
set _CL_=/utf-8
set PATH=c:\Python37%PLATFORM_PREFIX%;C:\Program Files%PROGRAM_FILES_PREFIX%\Java\jdk1.8.0;c:\Program Files\Git\usr\bin;c:\MinGW\bin;%PATH%
set ROOT_DIR=%~dp0\..\

mkdir build
cd build
@echo on
cmake .. -A %PLATFORM%
cmake --build . --config Release || goto :error
ctest -C Release --verbose || goto :error
cd python

rem https://www.appveyor.com/docs/windows-images-software/#python
rem call :BuildPython C:\Python34%PLATFORM_PREFIX%
rem call :BuildPython C:\Python35%PLATFORM_PREFIX%
rem call :BuildPython C:\Python36%PLATFORM_PREFIX%
rem call :BuildPython C:\Python37%PLATFORM_PREFIX%

cd %ROOT_DIR%
exit

:BuildPython
%1\python -m pip install -r %ROOT_DIR%\python\requirements-dev.txt || goto :error
%1\python %ROOT_DIR%\python\setup.py test bdist_wheel || goto :error
rmdir /Q /S build
del /S *.pyd
exit /B

:error
exit /B %errorlevel%

