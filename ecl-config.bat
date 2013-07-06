@ECHO OFF
REM Script converted from ecl-config
REM (Michael Goffioul)

IF %1 == --cflags (
	ECHO /EHsc /DGC_DLL /DGC_BUILD /nologo /D_CRT_SECURE_NO_DEPRECATE /DNDEBUG /MD /O2  -IE:/ecl-12.12.1/msvc/package/ecl
	GOTO END
) ELSE IF %1 == --libs (
	ECHO /link /incremental:no /nologo /nodefaultlib:libcmt /nodefaultlib:libcmtd /nodefaultlib:libc /nodefaultlib:libcd /nodefaultlib:msvcrtd.lib /link /LIBPATH:E:/ecl-12.12.1/msvc/package ecl.lib 
	GOTO END
)

ECHO Usage: ecl-config [OPTIONS]
ECHO Options:
ECHO      [--cflags]
ECHO      [--libs]

:END
