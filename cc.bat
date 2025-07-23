@echo off
setlocal enableextensions enabledelayedexpansion

echo --- Using cpp-%1 ...
cl main.cpp /std:c++%1 /Zc:__cplusplus /Zs /c
if %ERRORLEVEL% neq 0 (
    echo --- Compilation failed! Exiting...
    exit /b %ERRORLEVEL%
)
echo --- Compilation succeeded...
