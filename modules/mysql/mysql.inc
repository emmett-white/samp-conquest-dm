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

#include <YSI_Coding\y_hooks>

new
    MySQL:dbHandle;

/// -
/// Hooks
/// -

static MySQL_CreateConnection()
{
    new hostname[70];
    if(Env_Has("MYSQL_HOST")) {
        Env_Get("MYSQL_HOST", hostname, sizeof hostname);
    }
 
    new username[70];
    if(Env_Has("MYSQL_USER")) {
        Env_Get("MYSQL_USER", username, sizeof username);
    }
 
    new database[70];
    if(Env_Has("MYSQL_DATABASE")) {
        Env_Get("MYSQL_DATABASE", database, sizeof database);
    }
 
    new MySQLOpt: options = mysql_init_options();
    mysql_set_option(options, AUTO_RECONNECT, true);
    mysql_set_option(options, MULTI_STATEMENTS, true);
    mysql_set_option(options, POOL_SIZE, 2);

    dbHandle = mysql_connect(hostname, username, "", database, options);

    if (mysql_errno(dbHandle) != 0) {
        err("[MySQL]: Can't connect to database!");
        SendRconCommand("exit");
        return 1;
    }
    
    log("[MySQL]: Connection successfully");

    return 1;
}

hook OnGameModeInit()
{ 
    MySQL_CreateConnection();
    return 1;
}

hook OnGameModeExit()
{
    if(!mysql_close(dbHandle)) {
        err("Failed to terminate the database connection. Please check this.");
    }
    return 1;
}

stock MySQL:MySQL_GetHandle()
{
    return dbHandle;
}

// OnQueryError - REQUIRED
public OnQueryError(errorid, const error[], const callback[], const query[], MySQL:handle)
{
    return 1;
}

/// -
/// Functions
/// -

stock Task:MySQL_Query(const query[])
{
    return mysql_aquery(MySQL_GetHandle(), query, true);
}

stock Task:MySQL_QueryS(ConstStringTag:query)
{
    return mysql_aquery_s(MySQL_GetHandle(), query, true);
}