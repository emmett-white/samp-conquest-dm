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
/// Colors
/// -

#define SERVER 	    "{1C86EE}"
#define WHITE       "{FFFFFF}"

#define X11_SERVER 	0x1C86EEFF

/// -
/// Dialog
/// -

#define D_TITLE     ""SERVER"CONQUEST - "WHITE"ROLEPLAY"
#define D_CONFIRM 	""SERVER">"
#define D_CANCEL 	"CANCEL"

/// -
/// Messages
/// -

#define ServerMsg(%0,%1) \
    SendClientMessage(%0, X11_SERVER, "Conquest: "WHITE""%1)

#define ServerMsgF(%0,%1) \
    va_SendClientMessage(%0, X11_SERVER, "Conquest: "WHITE""%1)

#define ErrorMsg(%0,%1) \
  	SendClientMessage(%0, X11_INDIAN_RED_3, ""%1)

#define HelpMsg(%0,%1) \
  	SendClientMessage(%0, X11_GRAY, "USAGE: "%1)

#define ERR_MSG_AUTHORIZATION "You aren't authorized to use this command!"
#define ERR_MSG_ADUTY_REQUIRED "You must be on duty!"
#define ERR_MSG_INVALID_PLAYER_ID "Invalid player ID!"

/// -
/// Keys
/// -

#define HOLDING(%0) \
    ((newkeys & (%0)) == (%0))

#define RELEASED(%0) \
    (((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0)))


/// -
/// Limits
/// -

#define MIN_PASSWORD_LENGTH     6
#define MAX_PASSWORD_LENGTH     24

#undef MAX_COMMANDS
#define MAX_COMMANDS            (128)

#undef MAX_ACTORS
#define MAX_ACTORS              (24)

#define MESSAGE_MAX_LENGTH      124
#define ANNOUNCE_MAX_LENGTH     124