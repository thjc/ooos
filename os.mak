# Microsoft Developer Studio Generated NMAKE File, Based on OS.dsp
!IF "$(CFG)" == ""
CFG=OS - Win32 Debug
!MESSAGE No configuration specified. Defaulting to OS - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "OS - Win32 Release" && "$(CFG)" != "OS - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "OS.mak" CFG="OS - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "OS - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "OS - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "OS - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : 


CLEAN :
	-@erase 

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\OS.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\OS.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\OS.pdb" /machine:I386 /out:"$(OUTDIR)\OS.exe" 
LINK32_OBJS= \
	

!ELSEIF  "$(CFG)" == "OS - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : ".\.\Debug\OS" 


CLEAN :
	-@erase 
	-@erase ".\.\Debug\OS"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /Ze /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\OS.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\OS.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib LINK32_OBJS = "$(intdir)\boot.obj" /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\OS.pdb" /debug /machine:I386 /out:"$(OUTDIR)\OS.exe" /pdbtype:sept 
LINK32_OBJS= \
	

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("OS.dep")
!INCLUDE "OS.dep"
!ELSE 
!MESSAGE Warning: cannot find "OS.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "OS - Win32 Release" || "$(CFG)" == "OS - Win32 Debug"
SOURCE=.\boot.asm

!IF  "$(CFG)" == "OS - Win32 Release"

!ELSEIF  "$(CFG)" == "OS - Win32 Debug"

OutDir=.\Debug
TargetName=OS
InputPath=.\boot.asm

"$(INTDIR)\OS" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	cd $(OutDir) 
	ml /c /Fl /Fm /FR ..\$(InputPath) 
<< 
	

!ENDIF 


!ENDIF 

