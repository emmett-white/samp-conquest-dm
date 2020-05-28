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

ACMD:[4 && !IsPlayerAdmin(playerid)]admin(playerid, const params[])
{
    inline AdminMenu(id, dialogid, response, listitem, string: inputtext[]) {
        #pragma unused id, dialogid, inputtext

        if (!response)
            return 1;

        switch (listitem) {
            case 0: Admin_Config(playerid, 1); // Add admin
            case 1: Admin_Config(playerid, 2); // Update admin
            case 2: Admin_Config(playerid, 3); // Delete admin
        }
    }

    Dialog_ShowCallback(playerid, using inline AdminMenu, DIALOG_STYLE_LIST, ""SERVER"Admin Configuration",
        ""SERVER"> "WHITE"Add admin\n"SERVER"> "WHITE"Update admin\n"SERVER"> "WHITE"Remove admin", D_CONFIRM, D_CANCEL
    );
    return 1;
}

ACMD:[4]achangepass(playerid, const params[])
{
    static
        targetID,
        new_pass[MAX_PASSWORD_LENGTH];

    if (sscanf(params, "rs[" #MAX_PASSWORD_LENGTH "]", targetID, new_pass))
        return HelpMsg(playerid, "/achangepass [playerid] [password]");

    if (!(MIN_PASSWORD_LENGTH <= strlen(new_pass) <= MAX_PASSWORD_LENGTH))
        return ErrorMsg(playerid, "Password is too short or too long! (min. 6, max. 24 characters)");

    strcpy(Player_Password[targetID], new_pass);

    new String: Query = str_format("UPDATE `"TABLE_ACCOUNTS"` SET `account_password` = '%e' WHERE `account_id` = '%d'", Player_Password[targetID], Player_ID[targetID]);
    mysql_tquery_s(MySQL_GetHandle(), Query);

    ServerMsgF(playerid, "%s's password changed to %s.", PlayerName(targetID), Player_Password[targetID]);
    ServerMsgF(targetID, "IMPORTANT: Your new password is: "SERVER"%s "WHITE".", Player_Password[targetID]);
    return 1;
}