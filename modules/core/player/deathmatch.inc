/**
    @ Gamemode: Conquest DeathMatch
    @ Author: Emmett
    @ Date: 18th May
    @ Git: github.com/emmett-white/Conquest-DeathMatch
    @ Copyright (C) 2020

    @ About:
        - This community was founded in 2020 year..
        - Owner and Developer of this community is Emmett

    @ Credits:
        * Y-Less - YSI-Includes...
        * Incognito - Streamer
        * JustMichael - Discord help..
        * maddinat0r - MySQL
        * IllidanS4 - PawnPlus
        * AGraber - pawn-plus-mysql
        * urShadow - Pawn.RegEx
        * ziggi - Protection
        * Southclaws - sa-mp logger
        * Awesomedude - easyDialog
        * Emmet_ - New SA-MP callbacks
        * oscar-broman - weapon-config | SKY
        * kurta999's & IllidanS4 - YSF
        * dakyskye - Pawn ENV
**/

#include <YSI_Coding\y_hooks>

#define MAX_ARENA_MEMBERS   (10)

/// -
/// Arena Interiors
/// -

// IDs
#define LVPD_ID             (3)
#define SC_ID               (2)
#define WH1_ID              (1)
#define RCBG_ID             (10)

// Coordinates
#define LVPD_X              (288.745971)
#define LVPD_Y              (169.350997)
#define LVPD_Z              (1007.171875)
 
#define SC_X                (1204.809936)
#define SC_Y                (-11.586799)
#define SC_Z                (1000.921875)

#define WH1_X               (1412.639892)
#define WH1_Y               (-1.787510)
#define WH1_Z               (1000.924377)

#define RCBG_X              (-975.975708)
#define RCBG_Y              (1060.983032)
#define RCBG_Z              (1345.671875)

/// -
/// Variables
/// -

new
    Player_Arena[MAX_PLAYERS],
    Arena_Count[4];

/// -
/// Hooks
/// -

hook OnPlayerConnect(playerid)
{
    Player_Arena[playerid] =
    Arena_Count[0] =
    Arena_Count[1] =
    Arena_Count[2] =
    Arena_Count[3] = 0;
    return 1;
}

hook OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart)
{
    if (!Player_Arena[damagedid])
        return 0;
    return 1;
}

/// -
/// Functions
/// -

stock SetPlayerArena(const playerid, arena)
{
    switch (arena) {
        case 1: {
            if (Arena_Count[0] == MAX_ARENA_MEMBERS)
                return ErrorMsg(playerid, "That arena is full, please try again later...");

            Player_Arena[playerid] = 1;
            ++ Arena_Count[0];

            SetPlayerPos(playerid, LVPD_X, LVPD_Y, LVPD_Z);
            SetPlayerInterior(playerid, LVPD_ID);
            ServerMsg(playerid, "You've successfully joined.");

            GivePlayerWeapon(playerid, 24, cellmax);
            SetPlayerHealth(playerid, 99.0);
            SetPlayerArmour(playerid, 99.0);
        }

        case 2: {
            if (Arena_Count[1] == MAX_ARENA_MEMBERS)
                return ErrorMsg(playerid, "That arena is full, please try again later...");

            Player_Arena[playerid] = 2;
            ++ Arena_Count[1];

            SetPlayerPos(playerid, SC_X, SC_Y, SC_Z);
            SetPlayerInterior(playerid, SC_ID);
            ServerMsg(playerid, "You've successfully joined.");

            GivePlayerWeapon(playerid, 31, cellmax);
            GivePlayerWeapon(playerid, 24, cellmax);
            SetPlayerHealth(playerid, 99.0);
            SetPlayerArmour(playerid, 99.0);
        }

        case 3: {
            if (Arena_Count[2] == MAX_ARENA_MEMBERS)
                return ErrorMsg(playerid, "That arena is full, please try again later...");

            Player_Arena[playerid] = 3;
            ++ Arena_Count[2];

            SetPlayerPos(playerid, WH1_X, WH1_Y, WH1_Z);
            SetPlayerInterior(playerid, WH1_ID);
            ServerMsg(playerid, "You've successfully joined.");

            GivePlayerWeapon(playerid, 24, cellmax);
            SetPlayerHealth(playerid, 99.0);
            SetPlayerArmour(playerid, 99.0);
        }

        case 4: {
            if (Arena_Count[3] == MAX_ARENA_MEMBERS)
                return ErrorMsg(playerid, "That arena is full, please try again later...");

            Player_Arena[playerid] = 4;
            ++ Arena_Count[3];

            SetPlayerPos(playerid, RCBG_X, RCBG_Y, RCBG_Z);
            SetPlayerInterior(playerid, RCBG_ID);
            ServerMsg(playerid, "You've successfully joined.");

            GivePlayerWeapon(playerid, 24, cellmax);
            GivePlayerWeapon(playerid, 31, cellmax);
            GivePlayerWeapon(playerid, 34, cellmax);
            SetPlayerHealth(playerid, 99.0);
            SetPlayerArmour(playerid, 99.0);
        }
    }
    return 1;
}

/// -
/// Commands
/// -

CMD:arena(playerid, const params[])
{
    if (Player_Arena[playerid])
        return ErrorMsg(playerid, "You're already in an arena!");

    inline DialogArena(id, dialogid, response, listitem, string: inputtext[]) {
        #pragma unused id, dialogid, inputtext

        if (!response)
            return 1;

        switch (listitem) {
            case 0: SetPlayerArena(playerid, 1);
            case 1: SetPlayerArena(playerid, 2);
            case 2: SetPlayerArena(playerid, 3);
            case 3: SetPlayerArena(playerid, 4);
        }
    }

    Dialog_ShowCallbackF(playerid, using inline DialogArena, DIALOG_STYLE_TABLIST_HEADERS, D_TITLE,
        ""INDIAN_RED_3"Arena\tPlayers\n\
        "WHITE"LVPD\t"MEDIUM_SEA_GREEN"%d/"INDIAN_RED_3"10\n\
        "WHITE"Strip Club\t"MEDIUM_SEA_GREEN"%d/"INDIAN_RED_3"10\n\
        "WHITE"Warehouse 1\t"MEDIUM_SEA_GREEN"%d/"INDIAN_RED_3"10\n\
        "WHITE"RC Battlefield\t"MEDIUM_SEA_GREEN"%d/"INDIAN_RED_3"10",
        D_CONFIRM, D_CANCEL, Arena_Count[0], Arena_Count[1], Arena_Count[2], Arena_Count[3]
    );
    return 1;
}

CMD:lobby(playerid, const params[])
{
    if (!Player_Arena[playerid])
        return ErrorMsg(playerid, "You must be in an arena to use this command!");


    switch (Player_Arena[playerid]) {
        case 1: {
            Player_Arena[playerid] = 0;
            -- Arena_Count[0];

            Player_SpawnPos(playerid);
            SetPlayerArmour(playerid, 0.0);
            ResetPlayerWeapons(playerid);
        }

        case 2: {
            Player_Arena[playerid] = 0;
            -- Arena_Count[1];

            Player_SpawnPos(playerid);
            SetPlayerArmour(playerid, 0.0);
            ResetPlayerWeapons(playerid);
        }

        case 3: {
            Player_Arena[playerid] = 0;
            -- Arena_Count[2];

            Player_SpawnPos(playerid);
            SetPlayerArmour(playerid, 0.0);
            ResetPlayerWeapons(playerid);
        }

        case 4: {
            Player_Arena[playerid] = 0;
            -- Arena_Count[3];

            Player_SpawnPos(playerid);
            SetPlayerArmour(playerid, 0.0);
            ResetPlayerWeapons(playerid);
        }
    }
    return 1;
}