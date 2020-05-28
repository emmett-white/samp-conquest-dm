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
        - Y-Less - YSI-Includes...
        - Incognito - Streamer
        - JustMichael - Discord help..
        - maddinat0r - MySQL
        - urShadow - PawnPlus | PawnPlus-MySQL | Pawn.RegEx
        - ziggi - Protection
        - Southclaws - sa-mp logger
        - Awesomedude - easyDialog
        - Emmet_ - New SA-MP callbacks
        - oscar-broman - weapon-config | SKY
        - kurta999's & IllidanS4 - YSF
        - dakyskye - Pawn ENV
**/

public OnPlayerGetProtectionWarning(playerid, Protection:protection, bool:warn_reached, message[])
{
	static
		protection_name[32];

	Protection_GetParamString(protection, PROTECTION_NAME, protection_name);

	log(-1, "* Player: %d | Warn reached: %d | Name: %s | Message: %s",
        playerid, _:warn_reached, protection_name, message
    );
	return 1;
}