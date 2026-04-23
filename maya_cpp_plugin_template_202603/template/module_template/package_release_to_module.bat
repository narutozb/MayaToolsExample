@echo off
setlocal

set "SCRIPT_DIR=%~dp0"
set "TEMPLATE_ROOT=%SCRIPT_DIR%.."
set "RELEASE_DIR=%TEMPLATE_ROOT%out\maya2026\Release"
set "PLUGIN_DST_DIR=%SCRIPT_DIR%plug-ins"
set "SCRIPT_DST_DIR=%SCRIPT_DIR%scripts"

if not exist "%PLUGIN_DST_DIR%" mkdir "%PLUGIN_DST_DIR%"
if not exist "%SCRIPT_DST_DIR%" mkdir "%SCRIPT_DST_DIR%"

if not exist "%RELEASE_DIR%\hello_world_mll.mll" (
    echo Missing plugin: %RELEASE_DIR%\hello_world_mll.mll
    exit /b 1
)

if not exist "%RELEASE_DIR%\scene_tools_mll.mll" (
    echo Missing plugin: %RELEASE_DIR%\scene_tools_mll.mll
    exit /b 1
)

copy /Y "%RELEASE_DIR%\hello_world_mll.mll" "%PLUGIN_DST_DIR%\hello_world_mll.mll" >nul
copy /Y "%RELEASE_DIR%\scene_tools_mll.mll" "%PLUGIN_DST_DIR%\scene_tools_mll.mll" >nul

if exist "%TEMPLATE_ROOT%scripts\load_hello_plugin.py" (
    copy /Y "%TEMPLATE_ROOT%scripts\load_hello_plugin.py" "%SCRIPT_DST_DIR%\load_hello_plugin.py" >nul
)

if exist "%TEMPLATE_ROOT%scripts\load_scene_tools_plugin.py" (
    copy /Y "%TEMPLATE_ROOT%scripts\load_scene_tools_plugin.py" "%SCRIPT_DST_DIR%\load_scene_tools_plugin.py" >nul
)

echo Module package updated.
 echo %SCRIPT_DIR%

exit /b 0
