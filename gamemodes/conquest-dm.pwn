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

/// -
/// Includes
/// -

#include <a_samp>

#undef MAX_PLAYERS
#define MAX_PLAYERS             (32)

#include <a_mysql>
#include <env>

#include <streamer>

#define YSI_NO_HEAP_MALLOC
#define FOREACH_NO_BOTS
#define FOREACH_NO_STREAMED

#include <YSI_Data\y_iterate>
#include <YSI_Coding\y_timers>
#include <YSI_Data\y_bit>
#include <YSI_Server\y_colours>

#include <sscanf2>

#include <PawnPlus>
#include <pp-mysql>

#include <logger>

#include <YSI_Visual\y_dialog>
#include <YSI_Coding\y_inline>

#include <getspawninfo>
#include <weaponskill>
#include <protection>

#include <callbacks>
#include <shooting-textdraw>

#include <YSF>

#include <samp-profiler>

/// -
/// Server
/// -

#include "../modules/core/shortcuts.inc"
#include "../modules/utils/funcs.inc"
#include "../modules/utils/timers.inc"
#include "../modules/core/server/setup.inc"
// #include "../modules/core/server/protection.inc"

/// -
/// MySQL
/// -

#include "../modules/mysql/mysql.inc"

/// -
/// Player
/// -

#include "../modules/core/player/accounts.inc"
#include "../modules/core/player/chat.inc"
#include "../modules/core/player/anti-spawn-kill.inc"
#include "../modules/core/player/cmd-process.inc"
#include "../modules/core/player/commands.inc"

/// -
/// Systems
/// -

#include "../modules/core/player/deathmatch.inc"

/// -
/// Admin
/// -

#include "../modules/core/admin/core.inc"
#include "../modules/core/admin/commands.inc"

/// -
/// World
/// -

#include "../modules/world/maps.inc"

main() {}
