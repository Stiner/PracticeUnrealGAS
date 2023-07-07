@echo off

set CUR_DIR=%~dp0

for /f "tokens=*" %%a in ('"dir /b/s %CUR_DIR%\*.uproject"') do set PROJECT_PATH=%%a

set TOOL_PATH="%ProgramFiles(x86)%\Epic Games\Launcher\Engine\Binaries\Win64\UnrealVersionSelector.exe"

%TOOL_PATH% /projectfiles %PROJECT_PATH%