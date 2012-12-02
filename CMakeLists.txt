CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(PROJECT JustGame)
PROJECT(${PROJECT})
 
######################################################################
# Setting source files for this project
######################################################################
set(HEADERS
./src/PlayWorld/creators/ComponentsCreators.h
./src/PlayWorld/components/GraphBodyCom.h
./src/PlayWorld/components/PhysBodyCom.h
./src/PlayWorld/components/SoundBodyCom.h
./src/PlayWorld/components/HealthCom.h
./src/PlayWorld/components/PlayerControllableCom.h
./src/PlayWorld/components/AIControllableCom.h
./src/PlayWorld/components/CameraTrackableCom.h
./src/PlayWorld/components/WeaponCom.h
./src/PlayWorld/components/BulletCom.h
./src/PlayWorld/components/PlayerUICom.h
./src/PlayWorld/systems/BulletsSys.h
./src/PlayWorld/systems/PlayerControlSys.h
./src/PlayWorld/systems/PhysGraphSyncSys.h
./src/PlayWorld/systems/PlayerCameraSyncSys.h
./src/PlayWorld/systems/AIControlSys.h
./src/PlayWorld/systems/DamageSys.h
./src/PlayWorld/systems/PlayerGUISys.h
./src/PlayWorld/PlayWorld.h
)

set(SOURCES
./src/main.cpp
./src/PlayWorld/creators/ComponentsCreators.cpp
./src/PlayWorld/systems/BulletsSys.cpp
./src/PlayWorld/systems/PlayerControlSys.cpp
./src/PlayWorld/systems/PhysGraphSyncSys.cpp
./src/PlayWorld/systems/PlayerCameraSyncSys.cpp
./src/PlayWorld/systems/AIControlSys.cpp
./src/PlayWorld/systems/DamageSys.cpp
./src/PlayWorld/systems/PlayerGUISys.cpp
./src/PlayWorld/PlayWorld.cpp
)

set(CONFIGS
./configs
)

######################################################################
# Setting Qt packages
######################################################################
set(QT_ROOT $ENV{QT_ROOT})
set(QT_QMAKE_EXECUTABLE ${QT_ROOT}/bin/qmake)
set(QT_MOC_EXECUTABLE ${QT_ROOT}/bin/moc)
set(QT_RCC_EXECUTABLE ${QT_ROOT}/bin/rcc)
set(QT_UIC_EXECUTABLE ${QT_ROOT}/bin/uic)
set(QT_INCLUDE_DIR ${QT_ROOT}/include)
set(QT_LIBRARY_DIR ${QT_ROOT}/lib)
set(QT_QTCORE_LIBRARY ${QT_ROOT}/lib)
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

qt4_wrap_cpp(HEADERS_MOC ${HEADERS})

set(QT_DONT_USE_QTGUI true)

######################################################################
# Setting the directories of dependencies
######################################################################
set(OPENAL_SDK_DIR CACHE PATH FORCE)
if(OPENAL_SDK_DIR STREQUAL "")
message(SEND_ERROR "Please set directory where OpenAl sdk")
endif(OPENAL_SDK_DIR STREQUAL "")

set(FREEALUT_DIR CACHE PATH FORCE)
if(FREEALUT_DIR STREQUAL "")
message(SEND_ERROR "Please set directory where Freealut bin")
endif(FREEALUT_DIR STREQUAL "")

set(OGRE_INSTALL_DIR CACHE PATH FORCE)
if(OGRE_INSTALL_DIR STREQUAL "")
message(SEND_ERROR "Please set directory where Ogre install")
endif(OGRE_INSTALL_DIR STREQUAL "")

set(MYGUI_INSTALL_DIR CACHE PATH FORCE)
if(MYGUI_INSTALL_DIR STREQUAL "")
message(SEND_ERROR "Please set directory where MyGUI install")
endif(MYGUI_INSTALL_DIR STREQUAL "")

set(BULLET_INSTALL_DIR CACHE PATH FORCE)
if(BULLET_INSTALL_DIR STREQUAL "")
message(SEND_ERROR "Please set directory where Bullet install")
endif(BULLET_INSTALL_DIR STREQUAL "")

set(QT_INSTALL_DIR CACHE PATH FORCE)
if(QT_INSTALL_DIR STREQUAL "")
message(SEND_ERROR "Please set directory where Qt install")
endif(QT_INSTALL_DIR STREQUAL "")

set(JUSTGAMECORE_INSTALL_DIR CACHE PATH FORCE)
if(JUSTGAMECORE_INSTALL_DIR STREQUAL "")
message(SEND_ERROR "Please set directory where JustGameCore install")
endif(JUSTGAMECORE_INSTALL_DIR STREQUAL "")

set(JUSTGAMEMEDIA_DIR CACHE PATH FORCE)
if(JUSTGAMEMEDIA_DIR STREQUAL "")
message(SEND_ERROR "Please set directory where JustGameMedia")
endif(JUSTGAMEMEDIA_DIR STREQUAL "")

######################################################################
# Setting includes of dependencies
######################################################################
include_directories(
${OPENAL_SDK_DIR}/include
${FREEALUT_DIR}/include
${FREEALUT_DIR}/include/al
${OGRE_INSTALL_DIR}/include
${OGRE_INSTALL_DIR}/include/OIS
${OGRE_INSTALL_DIR}/include/OGRE
${MYGUI_INSTALL_DIR}/include/MYGUI
${BULLET_INSTALL_DIR}/include/bullet
${JUSTGAMECORE_INSTALL_DIR}/include
)

######################################################################
# Setting libs of dependencies
######################################################################
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
set(LIBRARIES
${JUSTGAMECORE_INSTALL_DIR}/lib/Debug/libJustGameCore_d.a
${OPENAL_SDK_DIR}/libs/Win32/OpenAL32.lib
${FREEALUT_DIR}/lib/alut.lib
${MYGUI_INSTALL_DIR}/lib/Debug/libMyGUI.OgrePlatform_d.a
${MYGUI_INSTALL_DIR}/lib/Debug/libMyGUIEngine_d.dll.a
${OGRE_INSTALL_DIR}/lib/debug/libOgreMain_d.dll.a
${OGRE_INSTALL_DIR}/lib/debug/libOIS_d.dll.a
${BULLET_INSTALL_DIR}/lib/libBulletSoftBody_Debug.a
${BULLET_INSTALL_DIR}/lib/libBulletDynamics_Debug.a
${BULLET_INSTALL_DIR}/lib/libBulletCollision_Debug.a
${BULLET_INSTALL_DIR}/lib/libLinearMath_Debug.a
)
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
set(LIBRARIES
${JUSTGAMECORE_INSTALL_DIR}/lib/Release/libJustGameCore.a
${OPENAL_SDK_DIR}/libs/Win32/OpenAL32.lib
${FREEALUT_DIR}/lib/alut.lib
${MYGUI_INSTALL_DIR}/lib/Release/libMyGUI.OgrePlatform.a
${MYGUI_INSTALL_DIR}/lib/Release/libMyGUIEngine.dll.a
${OGRE_INSTALL_DIR}/lib/release/libOgreMain.dll.a
${OGRE_INSTALL_DIR}/lib/release/libOIS.dll.a
${BULLET_INSTALL_DIR}/lib/libBulletSoftBody.a
${BULLET_INSTALL_DIR}/lib/libBulletDynamics.a
${BULLET_INSTALL_DIR}/lib/libBulletCollision.a
${BULLET_INSTALL_DIR}/lib/libLinearMath.a
)
endif(CMAKE_BUILD_TYPE STREQUAL "Release")

######################################################################
# Setting build options
######################################################################
if(CMAKE_BUILD_TYPE STREQUAL "")
set(CMAKE_BUILD_TYPE "Debug")
message(STATUS "Setting CMAKE_BUILD_TYPE to Debug")
endif(CMAKE_BUILD_TYPE STREQUAL "")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE})
add_executable(${PROJECT} WIN32 ${HEADERS} ${SOURCES} ${HEADERS_MOC})
target_link_libraries(${PROJECT} ${LIBRARIES} ${QT_LIBRARIES})

######################################################################
# Setting install rules
######################################################################
#all
INSTALL(DIRECTORY ${JUSTGAMEMEDIA_DIR}/
DESTINATION bin/Media
COMPONENT myinstall
PATTERN .git EXCLUDE
)

#Debug
INSTALL(
FILES
${CONFIGS}/debug/Plugins.cfg
${OGRE_INSTALL_DIR}/bin/debug/OgreMain_d.dll
${OGRE_INSTALL_DIR}/bin/debug/RenderSystem_GL_d.dll
${OGRE_INSTALL_DIR}/bin/debug/OIS_d.dll
${OGRE_INSTALL_DIR}/bin/debug/cg.dll
${MYGUI_INSTALL_DIR}/bin/debug/libMyGUIEngine_d.dll
${FREEALUT_DIR}/lib/alut.dll
${QT_INSTALL_DIR}/bin/QtCored4.dll
DESTINATION bin/Debug
CONFIGURATIONS Debug
)

INSTALL(
TARGETS ${PROJECT}
RUNTIME DESTINATION bin/Debug
CONFIGURATIONS Debug
)

#Release
INSTALL(
FILES
${CONFIGS}/release/Plugins.cfg
${OGRE_INSTALL_DIR}/bin/release/OgreMain.dll
${OGRE_INSTALL_DIR}/bin/release/RenderSystem_GL.dll
${OGRE_INSTALL_DIR}/bin/release/OIS.dll
${OGRE_INSTALL_DIR}/bin/release/cg.dll
${MYGUI_INSTALL_DIR}/bin/release/libMyGUIEngine.dll
${FREEALUT_DIR}/lib/alut.dll
${QT_INSTALL_DIR}/bin/QtCore4.dll
DESTINATION bin/Release
CONFIGURATIONS Release
)

INSTALL(
TARGETS ${PROJECT}
RUNTIME DESTINATION bin/Release
CONFIGURATIONS Release
)
