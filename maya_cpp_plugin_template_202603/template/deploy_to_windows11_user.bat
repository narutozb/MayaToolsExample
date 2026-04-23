@echo off
setlocal

set "SCRIPT_DIR=%~dp0"
set "PLUGIN_SRC=%SCRIPT_DIR%out\maya2026\Release\hello_world_mll.mll"
set "SCRIPT_SRC=%SCRIPT_DIR%scripts\load_hello_plugin.py"

set "MAYA_USER_ROOT=%USERPROFILE%\Documents\maya\2026"
set "PLUGIN_DST_DIR=%MAYA_USER_ROOT%\plug-ins"
set "SCRIPT_DST_DIR=%MAYA_USER_ROOT%\scripts"

if not exist "%PLUGIN_SRC%" (
    echo Release plugin not found:
    echo %PLUGIN_SRC%
    echo Please build Release before deployment.
    exit /b 1
)

if not exist "%SCRIPT_SRC%" (
    echo Loader script not found:
    echo %SCRIPT_SRC%
    exit /b 1
)

if not exist "%PLUGIN_DST_DIR%" mkdir "%PLUGIN_DST_DIR%"
if not exist "%SCRIPT_DST_DIR%" mkdir "%SCRIPT_DST_DIR%"

copy /Y "%PLUGIN_SRC%" "%PLUGIN_DST_DIR%\hello_world_mll.mll" >nul
if errorlevel 1 (
    echo Failed to copy plugin.
    exit /b 1
)

copy /Y "%SCRIPT_SRC%" "%SCRIPT_DST_DIR%\load_hello_plugin.py" >nul
if errorlevel 1 (
    echo Failed to copy script.
    exit /b 1
)

echo Deployment completed.

echo Plugin: %PLUGIN_DST_DIR%\hello_world_mll.mll

echo Script: %SCRIPT_DST_DIR%\load_hello_plugin.py

exit /b 0
