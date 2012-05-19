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

#Ќастройка подключени€ Qt
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

#√енераци€ мок файлов Qt
qt4_wrap_cpp(HEADERS_MOC ${HEADERS})

#”казание используемых модулей Qt
set(QT_DONT_USE_QTGUI true)

#”казание директорий с хеадерами зависимостей
include_directories(
D:/Dev/JustGameProject/ExternalDependencies/OpenAL_1.1_SDK/include
D:/Dev/JustGameProject/ExternalDependencies/freealut-1.1.0-bin/include
D:/Dev/JustGameProject/ExternalDependencies/freealut-1.1.0-bin/include/al
D:/Dev/JustGameProject/ExternalDependencies/Ogre_install/include
D:/Dev/JustGameProject/ExternalDependencies/Ogre_install/include/OIS
D:/Dev/JustGameProject/ExternalDependencies/Ogre_install/include/OGRE
D:/Dev/JustGameProject/ExternalDependencies/MyGUI_install/include/MYGUI
D:/Dev/JustGameProject/ExternalDependencies/Bullet/src
D:/Dev/JustGameProject/JustGameCore_sources
)

#”казание либ зависимостей дл€ дебага
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
set(LIBRARIES
D:/Dev/JustGameProject/JustGameCore_installed/lib/Debug/libJustGameCore_d.a
D:/Dev/JustGameProject/ExternalDependencies/OpenAL_1.1_SDK/libs/Win32/OpenAL32.lib
D:/Dev/JustGameProject/ExternalDependencies/freealut-1.1.0-bin/lib/alut.lib
D:/Dev/JustGameProject/ExternalDependencies/MyGUI_install/lib/Debug/libMyGUI.OgrePlatform_d.a
D:/Dev/JustGameProject/ExternalDependencies/MyGUI_install/lib/Debug/libMyGUIEngine_d.dll.a
D:/Dev/JustGameProject/ExternalDependencies/Ogre_install/lib/debug/libOgreMain_d.dll.a
D:/Dev/JustGameProject/ExternalDependencies/Ogre_install/lib/debug/libOIS_d.dll.a
D:/Dev/JustGameProject/ExternalDependencies/Bullet_build/lib/libBulletSoftBody_Debug.a
D:/Dev/JustGameProject/ExternalDependencies/Bullet_build/lib/libBulletDynamics_Debug.a
D:/Dev/JustGameProject/ExternalDependencies/Bullet_build/lib/libBulletCollision_Debug.a
D:/Dev/JustGameProject/ExternalDependencies/Bullet_build/lib/libLinearMath_Debug.a
)
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")

#”казание либ зависимостей дл€ релиза
if(CMAKE_BUILD_TYPE STREQUAL "Release")
set(LIBRARIES
D:/Dev/JustGameProject/JustGameCore_installed/lib/Release/libJustGameCore.a
D:/Dev/JustGameProject/ExternalDependencies/OpenAL_1.1_SDK/libs/Win32/OpenAL32.lib
D:/Dev/JustGameProject/ExternalDependencies/freealut-1.1.0-bin/lib/alut.lib
D:/Dev/JustGameProject/ExternalDependencies/MyGUI_install/lib/Release/libMyGUI.OgrePlatform.a
D:/Dev/JustGameProject/ExternalDependencies/MyGUI_install/lib/Release/libMyGUIEngine.dll.a
D:/Dev/JustGameProject/ExternalDependencies/Ogre_install/lib/release/libOgreMain.dll.a
D:/Dev/JustGameProject/ExternalDependencies/Ogre_install/lib/release/libOIS.dll.a
D:/Dev/JustGameProject/ExternalDependencies/Bullet_build/lib/libBulletSoftBody.a
D:/Dev/JustGameProject/ExternalDependencies/Bullet_build/lib/libBulletDynamics.a
D:/Dev/JustGameProject/ExternalDependencies/Bullet_build/lib/libBulletCollision.a
D:/Dev/JustGameProject/ExternalDependencies/Bullet_build/lib/libLinearMath.a
)
endif(CMAKE_BUILD_TYPE STREQUAL "Release")

#”казание пути где будут размещены бинарнике после билда
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE})
#”казание из чего будет построен бинарник
add_executable(${PROJECT} WIN32 ${SOURCES} ${HEADERS_MOC})
#”казание библиотек которые необходимо прилинковать
target_link_libraries(${PROJECT} ${LIBRARIES} ${QT_LIBRARIES})

#”казание действий при инстале в дебаге
INSTALL(TARGETS ${PROJECT}
RUNTIME DESTINATION bin/Debug
CONFIGURATIONS Debug)

#”казание действий при инстале в релизе
INSTALL(TARGETS ${PROJECT}
RUNTIME DESTINATION bin/Release
CONFIGURATIONS Release)
