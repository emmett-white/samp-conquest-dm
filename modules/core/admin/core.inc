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

#define MAX_ADMIN_LEVELS        (4)
#define TABLE_ADMINS            "player_admins"

new
    Char_Admin_ID[MAX_PLAYERS],
    Char_Admin_Name[MAX_PLAYERS][MAX_PLAYER_NAME],
    Char_Admin_Level[MAX_PLAYERS],
    Char_Admin_Code[MAX_PLAYERS];

/// -
/// Functions
/// -

forward Player_LoadAdmin(const playerid);
public Player_LoadAdmin(const playerid)
{
    if (cache_num_rows()) {
        cache_get_value_name_int(0, "admin_id", Char_Admin_ID[playerid]);
        cache_get_value_name(0, "admin_name", Char_Admin_Name[playerid]);
        cache_get_value_name_int(0, "admin_level", Char_Admin_Level[playerid]);
        cache_get_value_name_int(0, "admin_code", Char_Admin_Code[playerid]);
    }

    return 1;
}

stock SaveAdmin(const playerid)
{
    new String: Query = str_format("\
        UPDATE `"TABLE_ADMINS"` SET `admin_level` = '%d', `admin_code` = '%d' WHERE `admin_id` = '%d'",
        Char_Admin_Level[playerid], Char_Admin_Code[playerid], Char_Admin_ID[playerid]);
    mysql_tquery_s(MySQL_GetHandle(), Query);

    return 1;
}

stock Admin_VerifyCode(const playerid)
{
    if (Char_Admin_Level[playerid] >= 1) {
        inline SecurityCode(id, dialogid, response, listitem, string: inputtext[]) {
            #pragma unused id, dialogid, listitem

            if (!response)
                return Kick(playerid);

            if (!(strval(inputtext) == Char_Admin_Code[playerid]))
                Kick(playerid);
            else return 1;
        }

        Dialog_ShowCallbackF(playerid, using inline SecurityCode, DIALOG_STYLE_INPUT, ""SERVER"Admin Code", ""SERVER"%s, "WHITE"enter your correct admin code:", D_CONFIRM, D_CANCEL, PlayerName(playerid));
    }

    return 1;
}

forward db_insert_admin(const playerid);
public db_insert_admin(const playerid)
{
    Char_Admin_ID[playerid] = cache_insert_id();
    return 1;
}

stock Player_GetAdminLevel(const playerid)
{
    return Char_Admin_Level[playerid];
}

stock Admin_Config(const playerid, type)
{
    switch (type) {
        case 1: { // Add admin
            inline Admin_Menu_Add(id, dialogid, response, listitem, string: inputtext[]) {
                #pragma unused id, dialogid, listitem

                if (!response)
                    return 1;

                static
                    targetID,
                    level,
                    code;

                if (sscanf(inputtext, "ri", targetID, level))
                    return cmd_admin(playerid, "");

                if (!(1 <= level <= 4))
                    return ErrorMsg(playerid, "You can't go below 1 and above than 4!"), cmd_admin(playerid, "");

                if (level == Char_Admin_Level[targetID])
                    return ErrorMsg(playerid, "That player is already that admin level."), cmd_admin(playerid, "");


                Char_Admin_Level[targetID] = level;

                va_SendClientMessage(playerid, X11_SERVER, "[ADMIN]: You have set up an administrator level %d for player %s.", level, PlayerName(targetID));
                va_SendClientMessage(targetID, X11_SERVER, "[ADMIN]: Administrator %s has assigned you a level %d administrator.", PlayerName(playerid), level);

                code = random(999999999999999);
                Char_Admin_Code[playerid] = code;

                va_SendClientMessage(targetID, X11_SERVER, "[ADMIN-CODE]: Your admin security code is: %d", code);

                new String: Query = str_format("\
                    INSERT INTO `"TABLE_ADMINS"` (`admin_name`, `admin_level`, `admin_code`) \
                    VALUES ('%e', '%d', '%d')", PlayerName(targetID), level, Char_Admin_Code[playerid]);
                mysql_tquery_s(MySQL_GetHandle(), Query, "db_insert_admin", "d", playerid);
            }

            Dialog_ShowCallback(playerid, using inline Admin_Menu_Add, DIALOG_STYLE_INPUT, ""SERVER"Admin Menu - "WHITE"Add",
                ""SERVER"> "WHITE"Enter player id/name and level (1-4):", D_CONFIRM, D_CANCEL
            );
        }

        case 2: { // Update admin
            inline Admin_Menu_Update(id, dialogid, response, listitem, string: inputtext[]) {
                #pragma unused id, dialogid, listitem

                if (!response)
                    return 1;

                static
                    targetID,
                    level;

                if (sscanf(inputtext, "ri", targetID, level))
                    return cmd_admin(playerid, "");

                if (!(1 <= level <= 4))
                    return ErrorMsg(playerid, "You can't go below 1 and above than 4!"), cmd_admin(playerid, "");

                if (level == Char_Admin_Level[targetID])
                    return ErrorMsg(playerid, "That player is already that admin level."), cmd_admin(playerid, "");

                Char_Admin_Level[targetID] = level;

                new String: Query = str_format("UPDATE `"TABLE_ADMINS"` SET `admin_level` = '%d' WHERE `admin_name` = '%e'", Char_Admin_Level[targetID], PlayerName(targetID));
                mysql_tquery_s(MySQL_GetHandle(), Query);

                va_SendClientMessage(playerid, X11_SERVER, "[ADMIN]: You have update administrator level %d for player %s.", level, PlayerName(targetID));
                va_SendClientMessage(targetID, X11_SERVER, "[ADMIN]: Administrator %s has updated your admin level to %d.", PlayerName(playerid), level);
            }

            Dialog_ShowCallback(playerid, using inline Admin_Menu_Update, DIALOG_STYLE_INPUT, ""SERVER"Admin Menu - "WHITE"Update",
                ""SERVER"> "WHITE"Enter administrator id/name and level (1-4):", D_CONFIRM, D_CANCEL
            );
        }

        case 3: { // Delete admin
            inline Admin_Menu_Remove(id, dialogid, response, listitem, string: inputtext[]) {
                #pragma unused id, dialogid, listitem

                if (!response)
                    return 1;

                static targetID;

                if (sscanf(inputtext, "r", targetID))
                    return cmd_admin(playerid, "");

                if (targetID == INVALID_PLAYER_ID)
                    return ErrorMsg(playerid, "That player is offline!"), Admin_Config(playerid, 4);

                task_await(
                    MySQL_QueryS(
                        str_format(
                            "SELECT * FROM `"TABLE_ADMINS"` WHERE `admin_name` = '%e' LIMIT 1", PlayerName(targetID)
                        )
                    )
                );

                if (cache_num_rows()) {
                    new String: Query = str_format("DELETE FROM `"TABLE_ADMINS"` WHERE `admin_name` = '%e'", PlayerName(targetID));
                    mysql_tquery_s(MySQL_GetHandle(), Query);

                    Char_Admin_Level[targetID] = 0;
                    Char_Admin_Code[targetID] = 0;

                    va_SendClientMessage(playerid, X11_SERVER, "[ADMIN]: Administrator %s successfully removed.", PlayerName(targetID));
                    SendClientMessage(targetID, X11_INDIAN_RED_3, "[ADMIN]: You're no longer administrator.");
                } else ErrorMsg(playerid, "That player isn't administrator.");
            }

            Dialog_ShowCallback(playerid, using inline Admin_Menu_Remove, DIALOG_STYLE_INPUT, ""SERVER"Admin Menu - "WHITE"Remove",
                ""SERVER"> "WHITE"Enter administrator id/name:", D_CONFIRM, D_CANCEL
            );
        }

        case 4: { // Offline admin remove
            inline Admin_Menu_Offline_Remove(id, dialogid, response, listitem, string: inputtext[]) {
                #pragma unused id, dialogid, listitem

                if (!response)
                    return 1;

                static admin_name[MAX_PLAYER_NAME];

                if (sscanf(inputtext, "s[24]", admin_name))
                    return cmd_admin(playerid, "");

                task_await(
                    MySQL_QueryS(
                        str_format(
                            "SELECT * FROM `"TABLE_ADMINS"` WHERE `admin_name` = '%e' LIMIT 1", admin_name
                        )
                    )
                );

                if (cache_num_rows()) {
                    new String: Query = str_format("DELETE FROM `"TABLE_ADMINS"` WHERE `admin_name` = '%e'", admin_name);
                    mysql_tquery_s(MySQL_GetHandle(), Query);

                    va_SendClientMessage(playerid, X11_SERVER, "[ADMIN]: Administrator %s successfully removed.", admin_name);
                } else ErrorMsg(playerid, "That player isn't administrator.");
            }

            Dialog_ShowCallback(playerid, using inline Admin_Menu_Offline_Remove, DIALOG_STYLE_INPUT, ""SERVER"Admin Menu - "WHITE"Offline Remove",
                ""SERVER"> "WHITE"Enter administrator name:", D_CONFIRM, D_CANCEL
            );
        }
    }
    return 1;
}