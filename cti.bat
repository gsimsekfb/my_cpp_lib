@echo off
setlocal enableextensions enabledelayedexpansion

@REM Usage:
@REM cti list       // for `src/list.cpp`

clang-tidy src\%1.cpp -- -std=c++20
