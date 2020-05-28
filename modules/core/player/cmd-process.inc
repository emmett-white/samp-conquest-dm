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

/// By: Southclaws

#if defined CMD
    #undef CMD
#endif

#define CMD:%1(%2) forward cmd_%1(%2); public cmd_%1(%2)
#define ACMD:[%0]%1(%2,%3) CMD:%1(%2,%3) if (Player_GetAdminLevel(%2) < %0) return 0; else

public OnPlayerCommandText(playerid, cmdtext[])
{
	new
		cmd[30],
		params[127],
		cmdfunction[64],
		result = 1;

	sscanf(cmdtext, "s[30]s[127]", cmd, params);

	for (new i, j = strlen(cmd); i < j; i++)
		cmd[i] = tolower(cmd[i]);

	format(cmdfunction, 64, "cmd_%s", cmd[1]);

	if(funcidx(cmdfunction) == -1)
	{
		new
			iLvl = Player_GetAdminLevel(playerid),
			iLoop = 7;

		while(iLoop > 0)
		{
			format(cmdfunction, 64, "acmd_%s_%d", cmd[1], iLoop);

			if(funcidx(cmdfunction) != -1)
				break;

			iLoop--;
		}

		if(iLoop == 0)
			result = 0;

		if(iLvl < iLoop)
			result = 7;
	}

	if(result == 1) {
		if(isnull(params))result = CallLocalFunction(cmdfunction, "is", playerid, "\1");
		else result = CallLocalFunction(cmdfunction, "is", playerid, params);
	}

	/// if(0 < result < 7)
	/// 	log("[COMMAND] [%p]: %s", playerid, cmdtext);

	/// if (result == 0) ChatMsgLang(playerid, ORANGE, "CMDERROR0");

	/// else if	(result == 1) return 1;
	/// else if	(result == 2) ChatMsgLang(playerid, ORANGE, "CMDERROR1");
	/// else if	(result == 3) ChatMsgLang(playerid, RED, "CMDERROR2");
	/// else if	(result == 4) ChatMsgLang(playerid, RED, "CMDERROR3");
	/// else if	(result == 5) ChatMsgLang(playerid, RED, "CMDERROR4");
	/// else if	(result == 6) ChatMsgLang(playerid, RED, "CMDERROR5");
	return 1;
}