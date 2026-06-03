@echo off
setlocal enableextensions enabledelayedexpansion

@REM Usage:
@REM ct list            // test `src/list.cpp`
@REM ct list test-1     // test `src/list.cpp` `test-1`
@REM ct                 // test all test files under `src/*`
@REM ct algo-data\*
@REM ct algo-data\linked_list

@REM Troubleshoot: 
@REM build catch first if needed
@REM cl /std:c++20 /EHsc /c catch/catch_amalgamated.cpp /Fobuild\catch.obj

:: Check if %1 is empty
if "%~1"=="" (set "TEST_FILES=src\*.cpp") else (set "TEST_FILES=src\%1.cpp")

@REM for cl     : c++latest (for c++23)
@REM for clang++: c++23
set CPP_VERSION=c++23

echo .
echo -------------------------
echo Compilation
echo -------------------------
echo -- Using %CPP_VERSION%

@REM Print clang version and date
for /f "tokens=3" %%v in ('clang++ --version ^| find "clang version"') do (
    echo -- clang++ version: %%v
    curl -s "https://api.github.com/repos/llvm/llvm-project/releases/tags/llvmorg-%%v" | find "published_at"
)

echo -- build Catch first if needed, see ct.bat

set CMD=clang++ -std=%CPP_VERSION% -fexceptions -Wall -Wextra -Wpedantic -fcolor-diagnostics -g -O0 -Icatch %TEST_FILES% build\catch.obj -o build\tests.exe -luser32
echo -- cmd:
echo %CMD%
%CMD%
echo .

@REM other working cmds:
@REM clang++ -std=%CPP_VERSION% -fcolor-diagnostics main.cpp -o build/main.exe
@REM cl /std:%CPP_VERSION% /EHsc /Icatch %TEST_FILES% build\catch.obj /Fobuild\ /Febuild\tests.exe /link user32.lib


if %ERRORLEVEL% neq 0 (
    echo . & echo -- Compilation failed! Exiting...
    exit /b %ERRORLEVEL%
)
echo -- Compilation succeeded...
echo .

build\tests.exe -s %2
