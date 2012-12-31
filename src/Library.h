#ifndef LIBRARY_H
#define LIBRARY_H

namespace Components
{
    enum Components
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
        LoseMenuCom,
        WinMenuCom
    };
}

namespace Nodes
{
    enum Nodes
    {
        PlayerControlNode,
        AIControlNode,
        PhysGraphSyncNode,
        PlayerCameraSyncNode,
        BulletsNode,
        DoDamageNode,
        DamageableNode,
        PlayerStatNode,
        EnemyStatNode,
        GameGUINode,
        MainMenuNode,
        LoseMenuNode,
        WinMenuNode
    };
}

#endif
