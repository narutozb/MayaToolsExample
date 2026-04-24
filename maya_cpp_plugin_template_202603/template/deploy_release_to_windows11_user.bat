@echo off
setlocal

set "SCRIPT_DIR=%~dp0"
set "RELEASE_DIR=%SCRIPT_DIR%out\maya2026\Release"
set "MAYA_USER_ROOT=%USERPROFILE%\Documents\maya\2026"
set "PLUGIN_DST_DIR=%MAYA_USER_ROOT%\plug-ins"
set "SCRIPT_DST_DIR=%MAYA_USER_ROOT%\scripts"

rem TODO(project-manager): 如果后续要支持 2024/2025/2027 等版本部署，请把 2026 抽成参数。
if not exist "%RELEASE_DIR%\hello_world_mll.mll" (
    echo Missing plugin: %RELEASE_DIR%\hello_world_mll.mll
    exit /b 1
)

if not exist "%RELEASE_DIR%\scene_tools_mll.mll" (
    echo Missing plugin: %RELEASE_DIR%\scene_tools_mll.mll
    exit /b 1
)

if not exist "%RELEASE_DIR%\utility_tools_mll.mll" (
    echo Missing plugin: %RELEASE_DIR%\utility_tools_mll.mll
    exit /b 1
)

if not exist "%PLUGIN_DST_DIR%" mkdir "%PLUGIN_DST_DIR%"
if not exist "%SCRIPT_DST_DIR%" mkdir "%SCRIPT_DST_DIR%"

copy /Y "%RELEASE_DIR%\hello_world_mll.mll" "%PLUGIN_DST_DIR%\hello_world_mll.mll" >nul
copy /Y "%RELEASE_DIR%\scene_tools_mll.mll" "%PLUGIN_DST_DIR%\scene_tools_mll.mll" >nul
copy /Y "%RELEASE_DIR%\utility_tools_mll.mll" "%PLUGIN_DST_DIR%\utility_tools_mll.mll" >nul

if exist "%SCRIPT_DIR%scripts\load_hello_plugin.py" (
    copy /Y "%SCRIPT_DIR%scripts\load_hello_plugin.py" "%SCRIPT_DST_DIR%\load_hello_plugin.py" >nul
)

if exist "%SCRIPT_DIR%scripts\load_scene_tools_plugin.py" (
    copy /Y "%SCRIPT_DIR%scripts\load_scene_tools_plugin.py" "%SCRIPT_DST_DIR%\load_scene_tools_plugin.py" >nul
)

if exist "%SCRIPT_DIR%scripts\load_utility_tools_plugin.py" (
    copy /Y "%SCRIPT_DIR%scripts\load_utility_tools_plugin.py" "%SCRIPT_DST_DIR%\load_utility_tools_plugin.py" >nul
)

echo Deployment completed.
 echo %PLUGIN_DST_DIR%

exit /b 0
