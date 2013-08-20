#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc.exe
CCC=g++.exe
CXX=g++.exe
FC=gfortran.exe
AS=as.exe

# Macros
CND_PLATFORM=MinGW_1-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/ItemScreen.o \
	${OBJECTDIR}/src/Level.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/src/Unit.o \
	${OBJECTDIR}/src/UnitController.o \
	${OBJECTDIR}/src/CharacterScreen.o \
	${OBJECTDIR}/src/MainMenu.o \
	${OBJECTDIR}/src/Item.o \
	${OBJECTDIR}/src/GameScreen.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/C/Program\ Files\ \(x86\)/SDL_DEV/SDL-1.2.15/lib -L/C/Program\ Files\ \(x86\)/SDL_DEV/SDL_ttf-2.0.11/lib/x86 -L/C/Program\ Files\ \(x86\)/SDL_DEV/SDL_image-1.2.12/lib/x86 -L/C/Users/Cow/Documents/NetBeansProjects/Sprigen/dist/Dynamic/MinGW_1-Windows -lSDL_image -lSDL_ttf -lSDL.dll -lSDLmain -lSprigen

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/dasspiel.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/dasspiel.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/dasspiel ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/ItemScreen.o: src/ItemScreen.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL_ttf-2.0.11/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL_image-1.2.12/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL-1.2.15/include -Iinclude -I/C/Users/Cow/Documents/NetBeansProjects/Sprigen/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ItemScreen.o src/ItemScreen.cpp

${OBJECTDIR}/src/Level.o: src/Level.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL_ttf-2.0.11/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL_image-1.2.12/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL-1.2.15/include -Iinclude -I/C/Users/Cow/Documents/NetBeansProjects/Sprigen/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Level.o src/Level.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL_ttf-2.0.11/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL_image-1.2.12/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL-1.2.15/include -Iinclude -I/C/Users/Cow/Documents/NetBeansProjects/Sprigen/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/src/Unit.o: src/Unit.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL_ttf-2.0.11/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL_image-1.2.12/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL-1.2.15/include -Iinclude -I/C/Users/Cow/Documents/NetBeansProjects/Sprigen/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Unit.o src/Unit.cpp

${OBJECTDIR}/src/UnitController.o: src/UnitController.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL_ttf-2.0.11/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL_image-1.2.12/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL-1.2.15/include -Iinclude -I/C/Users/Cow/Documents/NetBeansProjects/Sprigen/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/UnitController.o src/UnitController.cpp

${OBJECTDIR}/src/CharacterScreen.o: src/CharacterScreen.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL_ttf-2.0.11/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL_image-1.2.12/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL-1.2.15/include -Iinclude -I/C/Users/Cow/Documents/NetBeansProjects/Sprigen/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/CharacterScreen.o src/CharacterScreen.cpp

${OBJECTDIR}/src/MainMenu.o: src/MainMenu.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL_ttf-2.0.11/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL_image-1.2.12/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL-1.2.15/include -Iinclude -I/C/Users/Cow/Documents/NetBeansProjects/Sprigen/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/MainMenu.o src/MainMenu.cpp

${OBJECTDIR}/src/Item.o: src/Item.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL_ttf-2.0.11/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL_image-1.2.12/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL-1.2.15/include -Iinclude -I/C/Users/Cow/Documents/NetBeansProjects/Sprigen/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Item.o src/Item.cpp

${OBJECTDIR}/src/GameScreen.o: src/GameScreen.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL_ttf-2.0.11/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL_image-1.2.12/include -I/C/Program\ Files\ \(x86\)/SDL_DEV/SDL-1.2.15/include -Iinclude -I/C/Users/Cow/Documents/NetBeansProjects/Sprigen/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/GameScreen.o src/GameScreen.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/dasspiel.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
