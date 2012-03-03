cmake_minimum_required (VERSION 2.8)

set(PROJECT JustGame)

project(${PROJECT})
 
set(HEADERS
./Bullet.h
./Enemy.h
./IGameObjectsListener.h
./LoadScreen.h
./LoseState.h
./MainMenuState.h
./MyGameObject.h
./Player.h
./PlayGameState.h
./SplashState.h
./WinState.h
)
 
set(SOURCES
./Bullet.cpp
./Enemy.cpp
./LoadScreen.cpp
./LoseState.cpp
./main.cpp
./MainMenuState.cpp
./MyGameObject.cpp
./Player.cpp
./PlayGameState.cpp
./SplashState.cpp
./WinState.cpp
)
 
include_directories(D:/Dev/ExternalDependencies/OpenAL_1.1_SDK/include
D:/Dev/ExternalDependencies/freealut-1.1.0-bin/include
D:/Dev/ExternalDependencies/freealut-1.1.0-bin/include/al
D:/Dev/ExternalDependencies/Ogre_installed/include
D:/Dev/ExternalDependencies/Ogre_installed/include/OIS
D:/Dev/ExternalDependencies/Ogre_installed/include/OGRE
D:/Dev/ExternalDependencies/MyGUI_installed/include/MYGUI
D:/Dev/ExternalDependencies/Bullet_sources/src
D:/Dev/JustGameProject/JustGameCore_sources
)

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
set(LIBRARIES
D:/Dev/JustGameProject/JustGameCore_installed/lib/Debug/libJustGameCore_d.a
D:/Dev/ExternalDependencies/OpenAL_1.1_SDK/libs/Win32/OpenAL32.lib
D:/Dev/ExternalDependencies/freealut-1.1.0-bin/lib/alut.lib
D:/Dev/ExternalDependencies/MyGUI_installed/lib/Debug/libMyGUI.OgrePlatform_d.a
D:/Dev/ExternalDependencies/MyGUI_installed/lib/Debug/libMyGUIEngine_d.dll.a
D:/Dev/ExternalDependencies/Ogre_installed/lib/debug/libOgreMain_d.dll.a
D:/Dev/ExternalDependencies/Ogre_installed/lib/debug/libOIS_d.dll.a
D:/Dev/ExternalDependencies/Bullet_builded/lib/libBulletSoftBody_Debug.a
D:/Dev/ExternalDependencies/Bullet_builded/lib/libBulletDynamics_Debug.a
D:/Dev/ExternalDependencies/Bullet_builded/lib/libBulletCollision_Debug.a
D:/Dev/ExternalDependencies/Bullet_builded/lib/libLinearMath_Debug.a
)
endif(${CMAKE_BUILD_TYPE} STREQUAL "Debug")

if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
set(LIBRARIES
D:/Dev/JustGameProject/JustGameCore_installed/lib/Release/libJustGameCore.a
D:/Dev/ExternalDependencies/OpenAL_1.1_SDK/libs/Win32/OpenAL32.lib
D:/Dev/ExternalDependencies/freealut-1.1.0-bin/lib/alut.lib
D:/Dev/ExternalDependencies/MyGUI_installed/lib/Release/libMyGUI.OgrePlatform.a
D:/Dev/ExternalDependencies/MyGUI_installed/lib/Release/libMyGUIEngine.dll.a
D:/Dev/ExternalDependencies/Ogre_installed/lib/release/libOgreMain.dll.a
D:/Dev/ExternalDependencies/Ogre_installed/lib/release/libOIS.dll.a
D:/Dev/ExternalDependencies/Bullet_builded/lib/libBulletSoftBody.a
D:/Dev/ExternalDependencies/Bullet_builded/lib/libBulletDynamics.a
D:/Dev/ExternalDependencies/Bullet_builded/lib/libBulletCollision.a
D:/Dev/ExternalDependencies/Bullet_builded/lib/libLinearMath.a
)
endif(${CMAKE_BUILD_TYPE} STREQUAL "Release")


set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE})
add_executable(${PROJECT} WIN32 ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT} ${LIBRARIES})


INSTALL(TARGETS ${PROJECT}
RUNTIME DESTINATION bin/Debug
CONFIGURATIONS Debug)

INSTALL(TARGETS ${PROJECT}
RUNTIME DESTINATION bin/Release
CONFIGURATIONS Release)
