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
/// Tables
/// -

#define TABLE_ACCOUNTS      "player_accounts"
#define TABLE_BANNED        "player_banned"
#define TABLE_CHARACTER     "player_character"

/// -
/// Variables
/// -

new
    Player_ID[MAX_PLAYERS],
    Player_Password[MAX_PLAYERS][256],
    Player_Login_Attempts[MAX_PLAYERS],

    // Character
    Char_ID[MAX_PLAYERS],
    Char_Sex[MAX_PLAYERS],
    Char_Skin[MAX_PLAYERS],
    Char_Money[MAX_PLAYERS],
    Char_Score[MAX_PLAYERS];


// Spawn positions
static Float:RANDOM_SPAWN_POS[][] = {
        // x        // y      // z      // a
    { -1265.4395, 2540.3528, 94.1224, 135.8056 },
    { -1276.1776, 2540.3862, 94.1224, 224.9028 },
    { -1285.7102, 2528.6941, 97.9968, 291.9098 },
    { -1298.7386, 2522.4412, 94.1267, 199.0082 },
    { -1317.7366, 2521.4524, 93.9766, 79.3529 },
    { -1325.5817, 2530.8813, 93.9766, 180.4769 },
    { -1341.2465, 2523.0762, 93.9766, 135.5602 },
    { -1349.2754, 2519.3630, 94.0347, 108.6400 },
    { -1355.5205, 2523.4021, 93.9766, 258.9495 },
    { -1363.0117, 2436.9148, 94.0543, 308.4071 },
    { -1359.3885, 2448.4763, 94.0633, 308.4071 },
    { -1358.7853, 2461.1917, 94.0633, 228.5142 },
    { -1341.8381, 2457.1804, 94.0633, 266.6812 },
    { -1339.4204, 2466.2380, 94.0381, 20.5684 }
};

/// -
/// Hooks
/// -

hook OnPlayerConnect(playerid)
{
    Player_Login_Attempts[playerid] = 0;

    task_await(
        MySQL_QueryS(
            str_format(
                "SELECT * FROM `"TABLE_BANNED"` WHERE `banned_pname` = '%e' LIMIT 1",
                PlayerName(playerid)
            )
        )
    );

    // Banned account
    if (cache_num_rows()) {
        static
            Admin_Name[MAX_PLAYER_NAME],
            Ban_Reason[MAX_PLAYER_NAME];

        cache_get_value_name(0, "banned_aname", Admin_Name);
        cache_get_value_name(0, "banned_reason", Ban_Reason);

        va_SendClientMessage(playerid, X11_INDIAN_RED, "%s, you're banned from this server.", PlayerName(playerid));
        va_SendClientMessage(playerid, X11_INDIAN_RED, "Admin: %s", Admin_Name);
        va_SendClientMessage(playerid, X11_INDIAN_RED, "Reason: %s", Ban_Reason);
        return 1;
    }

    Player_Check_Account(playerid);
    return 1;
}


/// -
/// Functions
/// -

static Player_Check_Account(const playerid)
{
    task_await(
        MySQL_QueryS(
            str_format(
                "SELECT * FROM `"TABLE_ACCOUNTS"` WHERE `account_name` = '%e' LIMIT 1",
                PlayerName(playerid)
            )
        )
    );

    // Registered
    if (cache_num_rows()) {
        // Account
        cache_get_value_name_int(0, "account_id", Player_ID[playerid]);
        cache_get_value_name(0, "account_password", Player_Password[playerid], 256);

        printf("%s", Player_Password[playerid]);
        printf("%d", Player_ID[playerid]);

        // Character
        task_await(
            MySQL_QueryS(
                str_format(
                    "SELECT * FROM `"TABLE_CHARACTER"` WHERE `char_name` = '%e' LIMIT 1", PlayerName(playerid)
                )
            )
        );

        if (cache_num_rows()) {
            // Character
            cache_get_value_name_int(0, "char_id", Char_ID[playerid]);
            cache_get_value_name_int(0, "char_sex", Char_Sex[playerid]);
            cache_get_value_name_int(0, "char_skin", Char_Skin[playerid]);
            cache_get_value_name_int(0, "char_money", Char_Money[playerid]);
            cache_get_value_name_int(0, "char_score", Char_Score[playerid]);
        }

        Auth_Register(playerid, 3);

        new String: Query = str_format("SELECT * FROM `player_admins` WHERE `admin_name` = '%e' LIMIT 1", PlayerName(playerid));
        mysql_tquery_s(MySQL_GetHandle(), Query, "Player_LoadAdmin", "d", playerid);
    } else {
        Auth_Register(playerid, 1);
    }
    return 1;
}

static Auth_Register(const playerid, type)
{
    switch (type) {
        case 1: { // Password
            inline DialogRegister(id, dialogid, response, listitem, string: inputtext[]) {
                #pragma unused id, dialogid, listitem

                if (!response)
                    return Kick(playerid);

                if (!(MIN_PASSWORD_LENGTH <= strlen(inputtext) <= MAX_PASSWORD_LENGTH))
                    return Dialog_ShowCallbackF(playerid, using inline DialogRegister, DIALOG_STYLE_INPUT,
                                D_TITLE,
                                ""SERVER"> "WHITE"%s, your account isn't registered, please, enter your desired password...",
                                D_CONFIRM, D_CANCEL, PlayerName(playerid)
                            );

                strcpy(Player_Password[playerid], inputtext);

                new String: Query = str_format(\
                    "INSERT INTO `"TABLE_ACCOUNTS"` (`account_name`, `account_password`) \
                    VALUES ('%e', '%e')", PlayerName(playerid), Player_Password[playerid]
                );
                mysql_tquery_s(MySQL_GetHandle(), Query, "db_insert_account", "d", playerid);

                new String: char_Query = str_format(\
                    "INSERT INTO `"TABLE_CHARACTER"` (`char_name`) VALUES ('%e')", PlayerName(playerid)
                );
                mysql_tquery_s(dbHandle, char_Query, "db_insert_character", "d", playerid);

                Auth_Register(playerid, 2);
            }

            Dialog_ShowCallbackF(playerid, using inline DialogRegister, DIALOG_STYLE_INPUT,
                D_TITLE,
                ""SERVER"> "WHITE"%s, your account isn't registered, please, enter your desired password...",
                D_CONFIRM, D_CANCEL, PlayerName(playerid)
            );
        }

        case 2: { // Gender
            inline DialogGender(id, dialogid, response, listitem, string: inputtext[]) {
                #pragma unused id, dialogid, listitem, inputtext

                Char_Sex[playerid] = (response == 1 ? 1 : 2); // 1 - Male | 2 - Female
                Char_Skin[playerid] = (response == 1 ? 26 : 12);

                Char_Money[playerid] = 20000;
                Char_Score[playerid] = 1;

                new String:Query = str_format("UPDATE `"TABLE_CHARACTER"` SET `char_sex` = '%d' WHERE `char_id` = '%d'", Char_Sex[playerid], Char_ID[playerid]);
                mysql_tquery_s(MySQL_GetHandle(), Query);

                Player_SpawnPos(playerid);

                SetPlayerSkin(playerid, Char_Skin[playerid]);
                GivePlayerMoney(playerid, Char_Money[playerid]);
                SetPlayerScore(playerid, Char_Score[playerid]);

                ClearChat(playerid, 40);
                SendClientMessage(playerid, -1, "Loading account...");

                SavePlayer(playerid);
            }

            Dialog_ShowCallback(playerid, using inline DialogGender, DIALOG_STYLE_MSGBOX, D_TITLE, "Choose gender (Male/Female)", "MALE", "FEMALE");
        }

        case 3: { // Login
            inline DialogLogin(id, dialogid, response, listitem, string: inputtext[]) {
                #pragma unused id, dialogid, listitem

                if (!response)
                    return Kick(playerid);


                if (!strcmp(inputtext, Player_Password[playerid], false)) {
                    Player_SpawnPos(playerid);

                    ClearChat(playerid, 40);
                    SendClientMessage(playerid, -1, "Loading account...");

                    SetPlayerSkin(playerid, Char_Skin[playerid]);
                    GivePlayerMoney(playerid, Char_Money[playerid]);
                    SetPlayerScore(playerid, Char_Score[playerid]);

                    Admin_VerifyCode(playerid);
                } else {
                    ++ Player_Login_Attempts[playerid];

                    SendClientMessage(playerid, X11_INDIAN_RED, "** Incorrect password, please, try again..");

                    Dialog_ShowCallbackF(playerid, using inline DialogLogin, DIALOG_STYLE_PASSWORD,
                        D_TITLE,
                        ""SERVER"> "WHITE"%s, your account is registered, please, enter your correct password...",
                        D_CONFIRM, D_CANCEL, PlayerName(playerid)
                    );

                    if (Player_Login_Attempts[playerid] == 3)
                        Kick(playerid);
                }
            }

            Dialog_ShowCallbackF(playerid, using inline DialogLogin, DIALOG_STYLE_PASSWORD,
                D_TITLE,
                ""SERVER"> "WHITE"%s, your account is registered, please, enter your correct password...",
                D_CONFIRM, D_CANCEL, PlayerName(playerid)
            );
        }
    }
    return 1;
}

forward db_insert_account(const playerid);
public db_insert_account(const playerid)
{
    Player_ID[playerid] = cache_insert_id();
    return 1;
}

forward db_insert_character(const playerid);
public db_insert_character(const playerid)
{
    Char_ID[playerid] = cache_insert_id();
    return 1;
}

stock SavePlayer(const playerid)
{
    new String: Query = str_format("\
        UPDATE `"TABLE_CHARACTER"` SET `char_sex` = '%d', `char_skin` = '%d', `char_money` = '%d', \
        `char_score` = '%d' WHERE `char_name` = '%e'", Char_Sex[playerid], Char_Skin[playerid], Char_Money[playerid],
        Char_Score[playerid], PlayerName(playerid));
    mysql_tquery_s(MySQL_GetHandle(), Query);
    return 1;
}

stock Player_SpawnPos(const playerid)
{
    new rand = random(sizeof(RANDOM_SPAWN_POS));
    SetSpawnInfo(
        playerid, 0, Char_Skin[playerid],
        RANDOM_SPAWN_POS[rand][0], RANDOM_SPAWN_POS[rand][1], RANDOM_SPAWN_POS[rand][2], RANDOM_SPAWN_POS[rand][3],
        0, 0, 0, 0, 0, 0
    );

    SpawnPlayer(playerid);

    TogglePlayerControllable(playerid, 0);
    defer SpawnTimer(playerid);

    SetPlayerHealth(playerid, 0x7FFFFFFF); // Infinite health
    return 1;
}

/// -
/// Timers
/// -

timer SpawnTimer[2000](playerid)
{
    SetPlayerSkin(playerid, Char_Skin[playerid]);

    TogglePlayerControllable(playerid, 1);
    SendClientMessage(playerid, -1, "Account successfully loaded.");
}