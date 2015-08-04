# Microsoft Developer Studio Project File - Name="main" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=main - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "main.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "main.mak" CFG="main - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "main - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "main - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "main - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I ".\src\scenegraph" /I ".\src\sgraph" /I ".\src\inc" /I ".\src" /I ".\src\sgraph_ext" /I ".\inc" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x416 /d "NDEBUG"
# ADD RSC /l 0x416 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /libpath:".\lib"

!ELSEIF  "$(CFG)" == "main - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I ".\src\sgraph" /I ".\src\inc" /I ".\src" /I ".\src\sgraph_ext" /I ".\inc" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x416 /d "_DEBUG"
# ADD RSC /l 0x416 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:".\lib"

!ENDIF 

# Begin Target

# Name "main - Win32 Release"
# Name "main - Win32 Debug"
# Begin Group "sgraph"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\sgraph\appearence.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\appearence.h
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\camera.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\camera.h
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\color.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\color.h
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\component.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\component.h
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\context.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\context.h
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\dlight.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\dlight.h
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\entity.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\entity.h
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\group.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\group.h
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\item.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\item.h
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\light.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\light.h
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\location.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\location.h
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\material.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\material.h
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\node.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\node.h
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\perspective.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\perspective.h
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\plight.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\plight.h
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\scene.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\scene.h
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\shape.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\shape.h
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\slight.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\slight.h
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\texture.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\texture.h
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\transformation.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sgraph\transformation.h
# End Source File
# End Group
# Begin Group "sgraph Extensions"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\sgraph_ext\billboard.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sgraph_ext\billboard.h
# End Source File
# Begin Source File

SOURCE=.\src\sgraph_ext\fog.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sgraph_ext\fog.h
# End Source File
# Begin Source File

SOURCE=.\src\sgraph_ext\font.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sgraph_ext\font.h
# End Source File
# Begin Source File

SOURCE=.\src\sgraph_ext\msh.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sgraph_ext\msh.h
# End Source File
# End Group
# Begin Group "inc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\inc\image.cpp
# End Source File
# Begin Source File

SOURCE=.\src\inc\image.h
# End Source File
# Begin Source File

SOURCE=.\src\inc\maths.cpp
# End Source File
# Begin Source File

SOURCE=.\src\inc\maths.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\src\dot.cpp
# End Source File
# Begin Source File

SOURCE=.\src\dot.h
# End Source File
# Begin Source File

SOURCE=.\src\dynamics.cpp
# End Source File
# Begin Source File

SOURCE=.\src\dynamics.h
# End Source File
# Begin Source File

SOURCE=.\src\engine.cpp
# End Source File
# Begin Source File

SOURCE=.\src\engine.h
# End Source File
# Begin Source File

SOURCE=.\src\engine_scene.cpp
# End Source File
# Begin Source File

SOURCE=.\src\engine_scene.h
# End Source File
# Begin Source File

SOURCE=.\src\main.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sgraph_ext\terrain.cpp
# End Source File
# Begin Source File

SOURCE=.\src\sgraph_ext\terrain.h
# End Source File
# Begin Source File

SOURCE=.\src\wheels.cpp
# End Source File
# Begin Source File

SOURCE=.\src\wheels.h
# End Source File
# End Target
# End Project
