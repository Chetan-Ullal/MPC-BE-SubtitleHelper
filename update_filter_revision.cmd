@ECHO OFF
SETLOCAL
PUSHD %~dp0

SET GIT_REV_BRANCH=LOCAL
SET GIT_REV_HASH=0
SET GIT_REV_COUNT=0
SET GIT_REV_DATE=0

SET gitexe="git.exe"
%gitexe% --version
IF /I %ERRORLEVEL%==0 GOTO :GIT_OK

SET gitexe="c:\Program Files\Git\cmd\git.exe"
IF NOT EXIST %gitexe% SET gitexe="c:\Program Files\Git\bin\git.exe"
IF NOT EXIST %gitexe% GOTO :SCRIPT_END

:GIT_OK

FOR /F "delims=" %%A IN ('%gitexe% describe --tags') DO (
  SET GIT_TAG_STR=%%A
)

IF NOT DEFINED GIT_TAG_STR GOTO :SCRIPT_END

FOR /F "tokens=1 delims=." %%A IN ("%GIT_TAG_STR%") DO (
  SET FILTER_MAJOR=%%A
)
FOR /F "tokens=2 delims=." %%A IN ("%GIT_TAG_STR%") DO (
  SET FILTER_MINOR=%%A
)
FOR /F "tokens=3 delims=.-" %%A IN ("%GIT_TAG_STR%") DO (
  SET FILTER_PATCH=%%A
)

IF NOT EXIST "revision.h" GOTO :UPDATE_REV

SET REVMAJOR=0
SET REVMINOR=0
SET REVPATCH=0
FOR /F "tokens=3,4 delims= " %%A IN ('FINDSTR /I /L /C:"define FILTER_VERSION_MAJOR" "revision.h"') DO SET REVMAJOR=%%A
FOR /F "tokens=3,4 delims= " %%A IN ('FINDSTR /I /L /C:"define FILTER_VERSION_MINOR" "revision.h"') DO SET REVMINOR=%%A
FOR /F "tokens=3,4 delims= " %%A IN ('FINDSTR /I /L /C:"define FILTER_VERSION_PATCH" "revision.h"') DO SET REVPATCH=%%A

IF NOT "%REVMAJOR%"=="%FILTER_MAJOR%" GOTO :UPDATE_REV
IF NOT "%REVMINOR%"=="%FILTER_MINOR%" GOTO :UPDATE_REV
IF NOT "%REVPATCH%"=="%FILTER_PATCH%" GOTO :UPDATE_REV

GOTO :DONT_UPDATE

:UPDATE_REV

ECHO.>> revision.h
ECHO // %GIT_TAG_STR% >> revision.h
ECHO #define FILTER_VERSION_MAJOR %FILTER_MAJOR% >> revision.h
ECHO #define FILTER_VERSION_MINOR %FILTER_MINOR% >> revision.h
ECHO #define FILTER_VERSION_PATCH %FILTER_PATCH% >> revision.h

ECHO The filter version is %GIT_TAG_STR%.

:SCRIPT_END
POPD
ENDLOCAL
EXIT /B

:DONT_UPDATE
ECHO The filter version is up to date.
GOTO :SCRIPT_END