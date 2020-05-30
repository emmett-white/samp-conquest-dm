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

/// -
/// Functions
/// -

stock BanPlayer(const targetID, const playerid, const reason[])
{
    va_SendClientMessage(playerid, X11_INDIAN_RED, "[BAN]: You've banned player %s because of %s.", PlayerName(targetID), reason);
    va_SendClientMessage(targetID, X11_INDIAN_RED, "[BAN]: You're banned from this server by %s because of %s.", PlayerName(playerid), reason);

    GameTextForPlayer(targetID, "~r~BANNED!", 10000, 3);

    new String: Query = str_format("INSERT INTO `"TABLE_BANNED"` (`banned_pname`, `banned_aname`, `banned_reason`) \
        VALUES ('%e', '%e', '%e')", PlayerName(targetID), PlayerName(playerid), reason);
    mysql_tquery_s(MySQL_GetHandle(), Query);
    return 1;
}

stock UnbanPlayer(const targetName[], const playerid)
{
    task_await(
        MySQL_QueryS(
            str_format(
                "SELECT * FROM `"TABLE_ACCOUNTS"` WHERE `account_name` = '%e' LIMIT 1", targetName
            )
        )
    );

    if (!cache_num_rows())
        return ErrorMsg(playerid, "That player doesn't exist in our database!");

    task_await(
        MySQL_QueryS(
            str_format(
                "SELECT * FROM `"TABLE_BANNED"` WHERE `banned_pname` = '%e' LIMIT 1", targetName
            )
        )
    );

    if (!cache_num_rows())
        return ErrorMsg(playerid, "That player isn't banned!");

    ServerMsgF(playerid, "You've unbanned player %s.", targetName);

    new String: Query = str_format("DELETE FROM `"TABLE_BANNED"` WHERE `banned_pname` = '%e'", targetName);
    mysql_tquery_s(MySQL_GetHandle(), Query);
    return 1;
}

stock OffBanPlayer(const targetName[], const playerid, const reason[])
{
    va_SendClientMessage(playerid, X11_INDIAN_RED, "[BAN]: You've off-banned player %s because of %s.", targetName, reason);

    new String: Query = str_format("INSERT INTO `"TABLE_BANNED"` (`banned_pname`, `banned_aname`, `banned_reason`) \
        VALUES ('%e', '%e', '%e')", targetName, PlayerName(playerid), reason);
    mysql_tquery_s(MySQL_GetHandle(), Query);
    return 1;
}