#ifndef COMPONENTSTYPES_H
#define COMPONENTSTYPES_H

namespace ComponentsTypes
{
    enum ComponentsTypes
    {
        MainMenuCom,
        GraphBodyCom,
        PhysBodyCom,
        SoundBodyCom,
        WeaponCom,
        PlayerControllableCom,
        AIControllableCom,
        CameraTrackableCom,
        BulletCom,
        HealthCom,
        PlayerUICom,
    };
}

namespace Nodes
{
    enum Nodes
    {
        PlayerControl,
        AIControl,
        PhysGraphSync,
        PlayerCameraSync,
        Bullets,
        DoDamage,
        Damageable,
        PlayerStat,
        EnemyStat,
        GameGUI,
        MainMenu
    };
}

#endif
