@ECHO OFF
REM Script to compile/link a C file with ECL
REM (Michael Goffioul)

set CMDTYPE=%1
set CMDARGS=
:LOOP
shift
IF NOT "%1" == "" (
	set CMDARGS=%CMDARGS% %1
	goto LOOP
)

IF %CMDTYPE% == --compile (
	cl /EHsc /DGC_DLL /DGC_BUILD /nologo /D_CRT_SECURE_NO_DEPRECATE /DNDEBUG /MD /O2  -IE:/ecl-12.12.1/msvc/package/ecl %CMDARGS%
	GOTO END
) ELSE IF %CMDTYPE% == --link (
	cl %CMDARGS% /link /incremental:no /nologo /nodefaultlib:libcmt /nodefaultlib:libcmtd /nodefaultlib:libc /nodefaultlib:libcd /nodefaultlib:msvcrtd.lib E:/ecl-12.12.1/msvc/package/ecl.lib
	GOTO END
)

ECHO Usage: %0 [OPTIONS] [ARGS*]
ECHO Options:
ECHO      [--compile]
ECHO      [--link]

:END
