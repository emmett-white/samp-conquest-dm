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

/// -
/// Server informations
/// -

#define SERVER_GAMEMODE	 		"Conquest | v1.0"
#define SERVER_MAPNAME	 		"San Andreas"
#define SERVER_LANGUAGE	 		"English"
#define SERVER_WEBURL	 		"www.conquest-dm.com"

/// -
/// Hook
/// -

hook OnGameModeInit()
{
	SetGameModeText(SERVER_GAMEMODE);
	SendRconCommand("mapname "SERVER_MAPNAME"");
	SendRconCommand("language "SERVER_LANGUAGE"");
	SendRconCommand("weburl "SERVER_WEBURL"");

    DisableInteriorEnterExits();

    Profiler_Start();

    /// enable all protections
    Protection_SetParamInt(PROTECTION_ALL, PROTECTION_ENABLED, 1);
    /// redefine name
    Protection_SetParamString(PROTECTION_TELEPORT, PROTECTION_NAME, "Teleport");

    // YSF | Allow nickname characters
    AllowNickNameCharacter('#', true);
    AllowNickNameCharacter(':', true);
	return 1;
}

hook OnGameModeExit()
{
    Profiler_Stop();
    return 1;
}