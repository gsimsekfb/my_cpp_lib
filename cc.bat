@echo off
setlocal enableextensions enabledelayedexpansion

echo --- Using cpp-20 ...

cl src\main.cpp /std:c++20 /Zc:__cplusplus /Zs /c

if %ERRORLEVEL% neq 0 (
    echo --- Compilation failed! Exiting...
    exit /b %ERRORLEVEL%
)
echo --- Compilation succeeded...
