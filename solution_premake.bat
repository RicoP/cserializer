@echo off
WHERE premake5 /Q
IF %ERRORLEVEL% NEQ 0 ECHO Download premake5 and put it into your PATH (https://premake.github.io/download/) && goto :EOF

premake5 vs2019
