@echo off
setlocal

if "%MAYA_LOCATION%"=="" (
    echo MAYA_LOCATION is not set.
    exit /b 1
)

cmake -S . -B build\maya2026_vs2022 -G "Visual Studio 17 2022" -A x64
if errorlevel 1 exit /b 1

cmake --build build\maya2026_vs2022 --config Debug
if errorlevel 1 exit /b 1

echo Build finished.
exit /b 0
