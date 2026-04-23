@echo off
setlocal

set "SCRIPT_DIR=%~dp0"
set "MODULE_ROOT=%SCRIPT_DIR%"
set "PLUGIN_DIR=%MODULE_ROOT%plug-ins"
set "SCRIPT_DST_DIR=%MODULE_ROOT%scripts"
set "USER_MODULES_DIR=%USERPROFILE%\Documents\maya\modules\MayaCppPluginTemplate"

if not exist "%PLUGIN_DIR%" mkdir "%PLUGIN_DIR%"
if not exist "%SCRIPT_DST_DIR%" mkdir "%SCRIPT_DST_DIR%"
if not exist "%USER_MODULES_DIR%" mkdir "%USER_MODULES_DIR%"

copy /Y "%MODULE_ROOT%MayaCppPluginTemplate.mod" "%USER_MODULES_DIR%\MayaCppPluginTemplate.mod" >nul
xcopy /E /I /Y "%PLUGIN_DIR%" "%USER_MODULES_DIR%\plug-ins" >nul
xcopy /E /I /Y "%SCRIPT_DST_DIR%" "%USER_MODULES_DIR%\scripts" >nul

echo Module template copied to:
 echo %USER_MODULES_DIR%

exit /b 0
