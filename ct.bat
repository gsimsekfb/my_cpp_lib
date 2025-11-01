@echo off
setlocal enableextensions enabledelayedexpansion

@REM Usage:
@REM ct list            // to test `src/list.cpp`
@REM ct list test-1     // to test `src/list.cpp` `test-1`
@REM ct         // to test all test files under `src/*`

@REM Troubleshoot: 
@REM build catch first if needed
@REM cl /std:c++20 /EHsc /c catch/catch_amalgamated.cpp /Fobuild\catch.obj

:: Check if %1 is empty
if "%~1"=="" (set "TEST_FILES=src\*.cpp") else (set "TEST_FILES=src\%1.cpp")

cl /std:c++20 /EHsc /Icatch %TEST_FILES% build\catch.obj /Fobuild\ /Febuild\tests.exe /link user32.lib

if %ERRORLEVEL% neq 0 (
    echo --- Compilation failed! Exiting...
    exit /b %ERRORLEVEL%
)
build\tests.exe -s %2
