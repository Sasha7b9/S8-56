@echo off

@echo %TIME%   Building Device ...

MSBuild.exe ..\..\generated\Device\Device56.vcxproj -clp:ErrorsOnly;WarningsOnly -nologo
set BUILD_STATUS=%ERRORLEVEL%
if not %BUILD_STATUS%==0 goto Failed

@echo %TIME%   Building Panel ...

MSBuild.exe ..\..\generated\Panel\Panel56.vcxproj -clp:ErrorsOnly;WarningsOnly -nologo
set BUILD_STATUS=%ERRORLEVEL%
if not %BUILD_STATUS%==0 goto Failed

goto Exit

rem @echo %TIME%   Building DeviceLoader ...
rem 
rem MSBuild.exe ..\..\generated\DeviceLoader\DeviceLoader.vcxproj -clp:ErrorsOnly;WarningsOnly -nologo
rem set BUILD_STATUS=%ERRORLEVEL%
rem if %BUILD_STATUS%==0 goto Success


:Failed
@echo %TIME%   !!!!!!!! ERROR !!!!!!!!!!!!!!!!!!!!!!!!!!!!! Build Failed !!!!!!
goto Exit

:Success
@echo %TIME%   Build success

:Exit

