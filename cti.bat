@echo off
setlocal enableextensions enabledelayedexpansion

@REM Usage:
@REM cti list       // for `src/list.cpp`

@REM for cl     : c++latest (for c++23)
@REM for clang++: c++23
set CPP_VERSION=c++23

echo .
echo -------------------------
echo Clang-tidy
echo -------------------------
echo -- using %CPP_VERSION%

for /f "tokens=3" %%v in ('clang++ --version ^| find "clang version"') do (
    echo -- clang++ version: %%v
    curl -s "https://api.github.com/repos/llvm/llvm-project/releases/tags/llvmorg-%%v" | find "published_at"
)

echo -- running clang-tidy ...
set CMD=clang-tidy src\%1.cpp -- -std=%CPP_VERSION%
echo -- cmd:
echo %CMD%
%CMD%
echo .
echo -- completed
