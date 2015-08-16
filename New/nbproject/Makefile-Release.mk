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
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/CAnimation.o \
	${OBJECTDIR}/CApp.o \
	${OBJECTDIR}/CArea.o \
	${OBJECTDIR}/CAreaScoring.o \
	${OBJECTDIR}/CBackground.o \
	${OBJECTDIR}/CBanzaiBill.o \
	${OBJECTDIR}/CBeanStalk.o \
	${OBJECTDIR}/CBlock.o \
	${OBJECTDIR}/CBlockPiece.o \
	${OBJECTDIR}/CCamera.o \
	${OBJECTDIR}/CCoin.o \
	${OBJECTDIR}/CDebugLogging.o \
	${OBJECTDIR}/CDragonCoin.o \
	${OBJECTDIR}/CEnemy.o \
	${OBJECTDIR}/CEntity.o \
	${OBJECTDIR}/CEntityCol.o \
	${OBJECTDIR}/CEvent.o \
	${OBJECTDIR}/CEventsManager.o \
	${OBJECTDIR}/CFireball.o \
	${OBJECTDIR}/CFramerate.o \
	${OBJECTDIR}/CGame.o \
	${OBJECTDIR}/CGameComplete.o \
	${OBJECTDIR}/CGameOver.o \
	${OBJECTDIR}/CGame_Initialize.o \
	${OBJECTDIR}/CGame_Loop.o \
	${OBJECTDIR}/CGame_OnEvent.o \
	${OBJECTDIR}/CGate.o \
	${OBJECTDIR}/CGateBar.o \
	${OBJECTDIR}/CGoomba.o \
	${OBJECTDIR}/CKoopaTroopaGreen.o \
	${OBJECTDIR}/CLevel.o \
	${OBJECTDIR}/CLevelTransition.o \
	${OBJECTDIR}/CMap.o \
	${OBJECTDIR}/CMario.o \
	${OBJECTDIR}/CPButton.o \
	${OBJECTDIR}/CPipe.o \
	${OBJECTDIR}/CPiranhaPlant.o \
	${OBJECTDIR}/CPlatform.o \
	${OBJECTDIR}/CPoints.o \
	${OBJECTDIR}/CPowerUp.o \
	${OBJECTDIR}/CQuestionBox.o \
	${OBJECTDIR}/CRex.o \
	${OBJECTDIR}/CRotatingBlock.o \
	${OBJECTDIR}/CRotatingPlatform.o \
	${OBJECTDIR}/CScreenFurniture.o \
	${OBJECTDIR}/CSoundManager.o \
	${OBJECTDIR}/CSplash.o \
	${OBJECTDIR}/CState.o \
	${OBJECTDIR}/CStateManager.o \
	${OBJECTDIR}/CStretchBlock.o \
	${OBJECTDIR}/CSurface.o \
	${OBJECTDIR}/CSurfaceManager.o \
	${OBJECTDIR}/CTile.o \
	${OBJECTDIR}/GlobalFunctions.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m64
CXXFLAGS=-m64

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=--64

# Link Libraries and Options
LDLIBSOPTIONS=`pkg-config --libs SDL_image` `pkg-config --libs SDL_ttf` `pkg-config --libs SDL_mixer`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mario

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mario: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mario ${OBJECTFILES} ${LDLIBSOPTIONS} `sdl-config --cflags --libs` -s

${OBJECTDIR}/CAnimation.o: CAnimation.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CAnimation.o CAnimation.cpp

${OBJECTDIR}/CApp.o: CApp.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CApp.o CApp.cpp

${OBJECTDIR}/CArea.o: CArea.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CArea.o CArea.cpp

${OBJECTDIR}/CAreaScoring.o: CAreaScoring.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CAreaScoring.o CAreaScoring.cpp

${OBJECTDIR}/CBackground.o: CBackground.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CBackground.o CBackground.cpp

${OBJECTDIR}/CBanzaiBill.o: CBanzaiBill.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CBanzaiBill.o CBanzaiBill.cpp

${OBJECTDIR}/CBeanStalk.o: CBeanStalk.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CBeanStalk.o CBeanStalk.cpp

${OBJECTDIR}/CBlock.o: CBlock.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CBlock.o CBlock.cpp

${OBJECTDIR}/CBlockPiece.o: CBlockPiece.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CBlockPiece.o CBlockPiece.cpp

${OBJECTDIR}/CCamera.o: CCamera.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CCamera.o CCamera.cpp

${OBJECTDIR}/CCoin.o: CCoin.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CCoin.o CCoin.cpp

${OBJECTDIR}/CDebugLogging.o: CDebugLogging.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CDebugLogging.o CDebugLogging.cpp

${OBJECTDIR}/CDragonCoin.o: CDragonCoin.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CDragonCoin.o CDragonCoin.cpp

${OBJECTDIR}/CEnemy.o: CEnemy.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CEnemy.o CEnemy.cpp

${OBJECTDIR}/CEntity.o: CEntity.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CEntity.o CEntity.cpp

${OBJECTDIR}/CEntityCol.o: CEntityCol.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CEntityCol.o CEntityCol.cpp

${OBJECTDIR}/CEvent.o: CEvent.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CEvent.o CEvent.cpp

${OBJECTDIR}/CEventsManager.o: CEventsManager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CEventsManager.o CEventsManager.cpp

${OBJECTDIR}/CFireball.o: CFireball.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CFireball.o CFireball.cpp

${OBJECTDIR}/CFramerate.o: CFramerate.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CFramerate.o CFramerate.cpp

${OBJECTDIR}/CGame.o: CGame.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CGame.o CGame.cpp

${OBJECTDIR}/CGameComplete.o: CGameComplete.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CGameComplete.o CGameComplete.cpp

${OBJECTDIR}/CGameOver.o: CGameOver.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CGameOver.o CGameOver.cpp

${OBJECTDIR}/CGame_Initialize.o: CGame_Initialize.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CGame_Initialize.o CGame_Initialize.cpp

${OBJECTDIR}/CGame_Loop.o: CGame_Loop.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CGame_Loop.o CGame_Loop.cpp

${OBJECTDIR}/CGame_OnEvent.o: CGame_OnEvent.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CGame_OnEvent.o CGame_OnEvent.cpp

${OBJECTDIR}/CGate.o: CGate.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CGate.o CGate.cpp

${OBJECTDIR}/CGateBar.o: CGateBar.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CGateBar.o CGateBar.cpp

${OBJECTDIR}/CGoomba.o: CGoomba.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CGoomba.o CGoomba.cpp

${OBJECTDIR}/CKoopaTroopaGreen.o: CKoopaTroopaGreen.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CKoopaTroopaGreen.o CKoopaTroopaGreen.cpp

${OBJECTDIR}/CLevel.o: CLevel.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CLevel.o CLevel.cpp

${OBJECTDIR}/CLevelTransition.o: CLevelTransition.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CLevelTransition.o CLevelTransition.cpp

${OBJECTDIR}/CMap.o: CMap.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CMap.o CMap.cpp

${OBJECTDIR}/CMario.o: CMario.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CMario.o CMario.cpp

${OBJECTDIR}/CPButton.o: CPButton.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CPButton.o CPButton.cpp

${OBJECTDIR}/CPipe.o: CPipe.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CPipe.o CPipe.cpp

${OBJECTDIR}/CPiranhaPlant.o: CPiranhaPlant.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CPiranhaPlant.o CPiranhaPlant.cpp

${OBJECTDIR}/CPlatform.o: CPlatform.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CPlatform.o CPlatform.cpp

${OBJECTDIR}/CPoints.o: CPoints.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CPoints.o CPoints.cpp

${OBJECTDIR}/CPowerUp.o: CPowerUp.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CPowerUp.o CPowerUp.cpp

${OBJECTDIR}/CQuestionBox.o: CQuestionBox.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CQuestionBox.o CQuestionBox.cpp

${OBJECTDIR}/CRex.o: CRex.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CRex.o CRex.cpp

${OBJECTDIR}/CRotatingBlock.o: CRotatingBlock.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CRotatingBlock.o CRotatingBlock.cpp

${OBJECTDIR}/CRotatingPlatform.o: CRotatingPlatform.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CRotatingPlatform.o CRotatingPlatform.cpp

${OBJECTDIR}/CScreenFurniture.o: CScreenFurniture.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CScreenFurniture.o CScreenFurniture.cpp

${OBJECTDIR}/CSoundManager.o: CSoundManager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CSoundManager.o CSoundManager.cpp

${OBJECTDIR}/CSplash.o: CSplash.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CSplash.o CSplash.cpp

${OBJECTDIR}/CState.o: CState.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CState.o CState.cpp

${OBJECTDIR}/CStateManager.o: CStateManager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CStateManager.o CStateManager.cpp

${OBJECTDIR}/CStretchBlock.o: CStretchBlock.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CStretchBlock.o CStretchBlock.cpp

${OBJECTDIR}/CSurface.o: CSurface.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CSurface.o CSurface.cpp

${OBJECTDIR}/CSurfaceManager.o: CSurfaceManager.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CSurfaceManager.o CSurfaceManager.cpp

${OBJECTDIR}/CTile.o: CTile.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/CTile.o CTile.cpp

${OBJECTDIR}/GlobalFunctions.o: GlobalFunctions.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s `pkg-config --cflags SDL_image` `pkg-config --cflags SDL_ttf` `pkg-config --cflags SDL_mixer`   -MMD -MP -MF $@.d -o ${OBJECTDIR}/GlobalFunctions.o GlobalFunctions.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/mario

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
