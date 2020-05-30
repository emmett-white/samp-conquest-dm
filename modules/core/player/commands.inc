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

CMD:skin(playerid, const params[])
{
    static skin_id;

    if (sscanf(params, "i", skin_id))
        return HelpMsg(playerid, "/skin [skin id]");

    if (!(1 <= skin_id <= 312))
        return ErrorMsg(playerid, "You can't go below 1 and above than 312!");

    Char_Skin[playerid] = skin_id;
    SetPlayerSkin(playerid, Char_Skin[playerid]);
    return 1;
}

CMD:changepass(playerid, const params[])
{
    if (!(MIN_PASSWORD_LENGTH <= strlen(params) <= MAX_PASSWORD_LENGTH))
        return ErrorMsg(playerid, "Password is too short or too long! (min. 6, max. 24 characters)");

    strcpy(Player_Password[playerid], params);

    new String: Query = str_format("UPDATE `"TABLE_ACCOUNTS"` SET `account_password` = '%e' WHERE `account_id` = '%d'", Player_Password[playerid], Player_ID[playerid]);
    mysql_tquery_s(MySQL_GetHandle(), Query);

    ServerMsgF(playerid, "Your new password is: "SERVER"%s "WHITE".", Player_Password[playerid]);
    return 1;
}