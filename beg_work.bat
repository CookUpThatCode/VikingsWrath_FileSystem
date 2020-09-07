CALL "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\Tools\VsDevCmd.bat"
REM for %%i in ("%~dp0.") do (set MULTIROOT=%%~dpi)
REM above goes up one directory
for %%i in ("%~dp0") do (set MULTIROOT=%%~dpi)
  echo MULTIROOT=%MULTIROOT%
cd %MULTIROOT%
code .


