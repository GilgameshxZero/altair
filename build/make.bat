@REM Proxy file that calls nmake with INCL set to all header directories.
@ECHO OFF
SETLOCAL ENABLEDELAYEDEXPANSION

@REM Careful to not exceed the 8192 string limit.
SET "INCL="

@REM Suppresses CMD terminate prompt.
nmake /C %* || CALL;
ENDLOCAL
