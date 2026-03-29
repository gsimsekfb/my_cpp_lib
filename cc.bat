@echo off
setlocal enableextensions enabledelayedexpansion

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

clang++ -std=%CPP_VERSION% -fcolor-diagnostics main.cpp
@REM cl main.cpp /std:%CPP_VERSION%

if %ERRORLEVEL% neq 0 (
    echo . & echo -- Compilation failed! Exiting...
    exit /b %ERRORLEVEL%
)
echo -- Compilation succeeded...
