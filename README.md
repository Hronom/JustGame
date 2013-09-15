Windows bash script for building JustGame
=============

    @echo off
    
    ::if u want build enter Y in "" example: "Y"
    SET build_JustGameCore="Y"
    SET build_JustGame="Y"
    
    ::set JustGameCore dirs
    SET JustGameCore_sources_dir="D:/Dev/JustGameProject/JustGameCore"
    SET JustGameCore_build_dir="D:/Dev/JustGameProject/JustGameCore_build"
    SET JustGameCore_install_dir="D:/Dev/JustGameProject/JustGameCore_install"
    
    ::set JustGameMedia_dir
    SET JustGameMedia_dir="D:/Dev/JustGameProject/JustGameMedia"
    
    ::set JustGame dirs
    SET JustGame_sources_dir="D:/Dev/JustGameProject/JustGame"
    SET JustGame_build_dir="D:/Dev/JustGameProject/JustGame_build"
    SET JustGame_install_dir="D:/Dev/JustGameProject/JustGame_install"
    
    ::set OgreDependencies dir
    SET OgreDependencies_install_dir="D:/Dev/JustGameProject/ExternalDependencies/OgreDependencies_install"
    
    ::set Ogre dir
    SET Ogre_install_dir="D:/Dev/JustGameProject/ExternalDependencies/Ogre_install"
    
    ::set MyGUI dir
    SET MyGUI_install_dir="D:/Dev/JustGameProject/ExternalDependencies/MyGUI_install"
    
    ::set Bullet dir
    SET Bullet_install_dir="D:/Dev/JustGameProject/ExternalDependencies/Bullet_install"
    
    ::set FreeAlut dir
    SET FreeAlut_dir="D:/Dev/JustGameProject/ExternalDependencies/freealut-1.1.0-bin"
    
    ::set OpenAL_SDK dir
    SET OpenAL_SDK_dir="D:/Dev/JustGameProject/ExternalDependencies/OpenAL_1.1_SDK"
    
    ::set Qt install dir
    SET Qt_install_dir="D:/Qt/qt-everywhere-opensource-src-4.8.3"
    
    if %build_JustGameCore% == "Y" (
    echo =======================================================
    echo ================ Build JustGameCore ===================
    echo =======================================================
    ::building JustGameCore
    RMDIR %JustGameCore_build_dir% /S /Q
    RMDIR %JustGameCore_install_dir% /S /Q
    MKDIR %JustGameCore_build_dir% 
    MKDIR %JustGameCore_install_dir%
    CD %JustGameCore_build_dir%
    cmake -G "MinGW Makefiles" -D CMAKE_INSTALL_PREFIX:STRING=%JustGameCore_install_dir% -D BULLET_INSTALL_DIR:STRING=%Bullet_install_dir% -D FREEALUT_DIR:STRING=%FreeAlut_dir% -D MYGUI_INSTALL_DIR:STRING=%MyGUI_install_dir% -D OGRE_INSTALL_DIR:STRING=%Ogre_install_dir% -D OPENAL_SDK_DIR:STRING=%OpenAL_SDK_dir% %JustGameCore_sources_dir%
    ::building Debug
    cmake -D CMAKE_BUILD_TYPE:STRING=Debug %JustGameCore_sources_dir%
    mingw32-make.exe
    mingw32-make.exe install
    ::building Release
    cmake -D CMAKE_BUILD_TYPE:STRING=Release %JustGameCore_sources_dir%
    mingw32-make.exe
    mingw32-make.exe install
    )
    
    if %build_JustGame% == "Y" (
    echo =======================================================
    echo ================== Build JustGame =====================
    echo =======================================================
    ::building JustGame
    RMDIR %JustGame_build_dir% /S /Q
    RMDIR %JustGame_install_dir% /S /Q
    MKDIR %JustGame_build_dir% 
    MKDIR %JustGame_install_dir%
    CD %JustGame_build_dir%
    cmake -G "MinGW Makefiles" -D CMAKE_INSTALL_PREFIX:STRING=%JustGame_install_dir% -D BULLET_INSTALL_DIR:STRING=%Bullet_install_dir% -D FREEALUT_DIR:STRING=%FreeAlut_dir% -D MYGUI_INSTALL_DIR:STRING=%MyGUI_install_dir% -D OGRE_INSTALL_DIR:STRING=%Ogre_install_dir% -D OPENAL_SDK_DIR:STRING=%OpenAL_SDK_dir% -D JUSTGAMECORE_INSTALL_DIR:STRING=%JustGameCore_install_dir% -D JUSTGAMEMEDIA_DIR:STRING=%JustGameMedia_dir% -D QT_INSTALL_DIR:STRING=%Qt_install_dir% %JustGame_sources_dir%
    ::building Debug
    cmake -D CMAKE_BUILD_TYPE:STRING=Debug %JustGame_sources_dir%
    mingw32-make.exe
    mingw32-make.exe install
    ::building Release
    cmake -D CMAKE_BUILD_TYPE:STRING=Release %JustGame_sources_dir%
    mingw32-make.exe
    mingw32-make.exe install
    )
    
    
    
    pause

Windows bash script for building dependencies
=============

    @echo off
    
    ::if u want build enter Y in "" example: "Y"
    SET build_OgreDependencies="Y"
    SET build_Ogre="Y"
    SET build_MyGUI="Y"
    SET build_Bullet="Y"
    
    ::set OgreDependencies dirs
    SET OgreDependencies_sources_dir="D:/Dev/JustGameProject/ExternalDependencies/OgreDependencies"
    SET OgreDependencies_build_dir="D:/Dev/JustGameProject/ExternalDependencies/OgreDependencies_build"
    SET OgreDependencies_install_dir="D:/Dev/JustGameProject/ExternalDependencies/OgreDependencies_install"
    
    ::set Ogre dirs
    SET Ogre_sources_dir="D:/Dev/JustGameProject/ExternalDependencies/Ogre"
    SET Ogre_build_dir="D:/Dev/JustGameProject/ExternalDependencies/Ogre_build"
    SET Ogre_install_dir="D:/Dev/JustGameProject/ExternalDependencies/Ogre_install"
    
    ::set MyGUI dirs
    SET MyGUI_sources_dir="D:/Dev/JustGameProject/ExternalDependencies/MyGUI"
    SET MyGUI_build_dir="D:/Dev/JustGameProject/ExternalDependencies/MyGUI_build"
    SET MyGUI_install_dir="D:/Dev/JustGameProject/ExternalDependencies/MyGUI_install"
    
    ::set Bullet dirs
    SET Bullet_sources_dir="D:/Dev/JustGameProject/ExternalDependencies/Bullet"
    SET Bullet_build_dir="D:/Dev/JustGameProject/ExternalDependencies/Bullet_build"
    SET Bullet_install_dir="D:/Dev/JustGameProject/ExternalDependencies/Bullet_install"
    
    
    
    if %build_OgreDependencies% == "Y" (
    echo =======================================================
    echo ============= Build Ogre3D dependencies ===============
    echo =======================================================
    ::building OgreDependencies
    RMDIR %OgreDependencies_build_dir% /S /Q
    RMDIR %OgreDependencies_install_dir% /S /Q
    MKDIR %OgreDependencies_build_dir% 
    MKDIR %OgreDependencies_install_dir%
    CD %OgreDependencies_build_dir%
    cmake -G "MinGW Makefiles" -D CMAKE_INSTALL_PREFIX:STRING=%OgreDependencies_install_dir% %OgreDependencies_sources_dir%
    ::building Debug
    cmake -D CMAKE_BUILD_TYPE:STRING=Debug %OgreDependencies_sources_dir%
    mingw32-make.exe
    mingw32-make.exe install
    ::building Release
    cmake -D CMAKE_BUILD_TYPE:STRING=Release %OgreDependencies_sources_dir%
    mingw32-make.exe
    mingw32-make.exe install
    )
    
    
    
    if %build_Ogre% == "Y" (
    echo =======================================================
    echo ==================== Build Ogre3D =====================
    echo =======================================================
    ::building Ogre
    RMDIR %Ogre_build_dir% /S /Q
    RMDIR %Ogre_install_dir% /S /Q
    MKDIR %Ogre_build_dir%
    MKDIR %Ogre_install_dir%
    CD %Ogre_build_dir%
    cmake -G "MinGW Makefiles" -D OGRE_DEPENDENCIES_DIR:STRING=%OgreDependencies_install_dir% -D CMAKE_INSTALL_PREFIX:STRING=%Ogre_install_dir% -D OGRE_BUILD_RENDERSYSTEM_D3D9:BOOL=false -D OGRE_BUILD_RENDERSYSTEM_D3D11:BOOL=false -D OGRE_BUILD_RENDERSYSTEM_GL:BOOL=true -D OGRE_BUILD_SAMPLES:BOOL=false -D OGRE_BUILD_TOOLS:BOOL=true -D OGRE_INSTALL_SAMPLES:BOOL=false %Ogre_sources_dir%
    ::building Debug
    cmake -D CMAKE_BUILD_TYPE:STRING=Debug %Ogre_sources_dir%
    mingw32-make.exe
    mingw32-make.exe install
    ::building Release
    cmake -D CMAKE_BUILD_TYPE:STRING=Release %Ogre_sources_dir%
    mingw32-make.exe
    mingw32-make.exe install
    )
    
    
    
    if %build_MyGUI% == "Y" (
    echo =======================================================
    echo ==================== Build MyGUI ======================
    echo =======================================================
    ::building MyGUI
    RMDIR %MyGUI_build_dir% /S /Q
    RMDIR %MyGUI_install_dir% /S /Q
    MKDIR %MyGUI_build_dir%
    MKDIR %MyGUI_install_dir%
    CD %MyGUI_build_dir%
    cmake -G "MinGW Makefiles" -D MYGUI_DEPENDENCIES_DIR:STRING=%OgreDependencies_install_dir% -D OGRE_SOURCE:STRING=%Ogre_sources_dir% -D OGRE_BUILD:STRING=%Ogre_install_dir% -D MYGUI_DONT_USE_OBSOLETE:BOOL=true -D MYGUI_BUILD_PLUGINS:BOOL=false -D MYGUI_BUILD_DEMOS:BOOL=false -D MYGUI_BUILD_TOOLS:BOOL=false -D MYGUI_INSTALL_MEDIA:BOOL=true -D MYGUI_INSTALL_SAMPLES:BOOL=false -D MYGUI_INSTALL_TOOLS:BOOL=true -D CMAKE_INSTALL_PREFIX:STRING=%MyGUI_install_dir% %MyGUI_sources_dir%
    ::building Debug
    cmake -D CMAKE_BUILD_TYPE:STRING=Debug %MyGUI_sources_dir%
    mingw32-make.exe
    mingw32-make.exe install
    ::building Release
    cmake -D CMAKE_BUILD_TYPE:STRING=Release %MyGUI_sources_dir%
    mingw32-make.exe
    mingw32-make.exe install
    )
    
    
    
    if %build_Bullet% == "Y" (
    echo =======================================================
    echo ================ Build Bullet physics  ================
    echo =======================================================
    ::building Bullet
    RMDIR %Bullet_build_dir% /S /Q
    RMDIR %Bullet_install_dir% /S /Q
    MKDIR %Bullet_build_dir%
    MKDIR %Bullet_install_dir%
    CD %Bullet_build_dir%
    cmake -G "MinGW Makefiles" -D BUILD_DEMOS:BOOL=false -D BUILD_EXTRAS:BOOL=false -D INSTALL_LIBS:BOOL=true -D CMAKE_INSTALL_PREFIX:STRING=%Bullet_install_dir% %Bullet_sources_dir%
    ::building Debug
    cmake -D CMAKE_BUILD_TYPE:STRING=Debug %Bullet_sources_dir%
    mingw32-make.exe
    mingw32-make.exe install
    ::building Release
    cmake -D CMAKE_BUILD_TYPE:STRING=Release %Bullet_sources_dir%
    mingw32-make.exe
    mingw32-make.exe install
    )
    
    pause
