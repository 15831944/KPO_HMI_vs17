rem Set the environment variable MSOFFICE_DIR
rem This variable is the important path to the MS Office
rem Example: set MSOFFICE_DIR="C:\Program Files\Microsoft Office\Office10"
rem The environment variable PRJDIR must be set in the custom build step.
rem This variable is used in the batch file to address the actual working directory
rem Example of the entries for the custom build step:
rem    set PRJDIR=$(ProjectDir)  						    
rem    ..\..\Macros\generate_telcom.bat

@echo off

if not exist "%MSOFFICE_DIR%" goto:wrongEnv goto wrongEnv

set auto_macro=1
del /F "%APPDATA%\Microsoft\Office\Recent\*.xla.LNK"
copy /Y ..\..\Macros\GenerateTelcomFiles.xla "%MSOFFICE_DIR%\XLStart\"

if exist "%TELCOMDIR%\tdl\bin\gen.bat" goto extendExit

goto exitScript

:extendExit
	copy /Y "%TELCOMDIR%\tdl\bin\gen.bat" "%TELCOMDIR%\tdl\bin\autogen.bat"
        attrib -R "%TELCOMDIR%\tdl\bin\autogen.bat"        
        echo exit 0 >> "%TELCOMDIR%\tdl\bin\autogen.bat"


"%MSOFFICE_DIR%\excel.exe"

del /F "%MSOFFICE_DIR%\XLStart\GenerateTelcomFiles.xla"

del /F "%TELCOMDIR%\tdl\bin\autogen.bat"

exit 0

:wrongEnv
echo Please specify environment variable MSOFFICE_DIR. See .\..\Macros\generate_telcom.bat!!
exit 1

:exitScript
echo %TELCOMDIR%\tdl\bin\gen.bat doesn't exist. Please check your telcom environment
exit 1 
