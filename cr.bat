@echo off
setlocal enableextensions enabledelayedexpansion

@REM v1: w/ cmake==
@REM ===========================
@REM cd build	
@REM cmake --build .

@REM rem ...
@REM Debug\hello.exe



@REM v2: w/o cmake
@REM ===========================
@REM e.g. cl main.cpp /std:c++20 /Fobuild\ /Febuild\main.exe
@REM cl main.cpp /std:c++%1 /Fobuild\ /Febuild\main.exe


echo --- Using cpp-%1 ...
cl main.cpp /std:c++%1 /Zc:__cplusplus /Fobuild\ /Febuild\main.exe
if %ERRORLEVEL% neq 0 (
    echo --- Compilation failed! Exiting...
    exit /b %ERRORLEVEL%
)
echo --- Compilation succeeded...

build\main.exe



@REM Todo
@REM 
@REM v3: compiles if the source file is newer than the executable
@REM ===========================
@REM This script:
@REM First checks if main.exe exists at all - if not, we need to compile
@REM If it exists, compares the timestamp of main.cpp with main.exe
@REM Only compiles if the source file is newer than the executable

@REM if not exist main.exe goto compile

@REM set SRC_FILE=main.cpp
@REM set EXE_FILE=main.exe

@REM REM Get timestamps and sizes for both files
@REM for %%i in (%SRC_FILE%) do set SRC_TIME=%%~ti & set SRC_SIZE=%%~zi
@REM for %%i in (%EXE_FILE%) do set EXE_TIME=%%~ti & set EXE_SIZE=%%~zi

@REM REM Compare both timestamp and size
@REM if "%SRC_TIME%" gtr "%EXE_TIME%" goto compile

@REM goto run

@REM :compile
@REM echo Compiling %SRC_FILE%...

@REM cl main.cpp
@REM if %ERRORLEVEL% neq 0 (
@REM     echo --- Compilation failed! Exiting...
@REM     exit /b %ERRORLEVEL%
@REM )

@REM :run
@REM main.exe