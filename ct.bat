@echo off
setlocal enableextensions enabledelayedexpansion

echo =========================================================================
echo --- Usage Hint: "ct vec 20" means "test vec.cpp with cpp20" ...
echo =========================================================================
echo .

echo --- Using cpp-%2 ...
cl /std:c++%2 /Zc:__cplusplus /EHsc /Icatch %1.cpp catch/catch_amalgamated.cpp /Fobuild\ /Febuild\tests.exe /link user32.lib
if %ERRORLEVEL% neq 0 (
    echo --- Compilation failed! Exiting...
    exit /b %ERRORLEVEL%
)
echo --- Compilation succeeded...

build\tests.exe -s


@REM todos
@REM - if no arg, test all files