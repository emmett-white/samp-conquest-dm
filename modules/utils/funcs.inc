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
/// Forwards
/// -

forward [MAX_PLAYER_NAME + 1]PlayerName(playerid);

/// -
/// Natives
/// -

native STREAMER_TAG_3D_TEXT_LABEL:CreateFormattedLabel(ConstAmxString:text, color, Float:x, Float:y, Float:z, Float:drawdistance, attachedplayer = INVALID_PLAYER_ID, attachedvehicle = INVALID_VEHICLE_ID, testlos = 0, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_3D_TEXT_LABEL_SD, STREAMER_TAG_AREA:areaid = STREAMER_TAG_AREA:-1, priority = 0) = CreateDynamic3DTextLabel;
native Update3DLabelString(STREAMER_TAG_3D_TEXT_LABEL:id, color, ConstAmxString:text) = UpdateDynamic3DTextLabelText;

/// -
/// Functions
/// -

stock PlayerName(playerid)
{
	#assert MAX_PLAYER_NAME + 1 == 25
	#emit PUSH.C 25
	#emit PUSH.S 16
	#emit PUSH.S playerid
	#emit PUSH.C 12
	#emit SYSREQ.C GetPlayerName
	#emit STACK 16
	#emit RETN
}


stock ClearChat (const playerid, lines)
{
	for (new i = 0; i < lines; ++i)
		SendClientMessage(playerid, -1, " ");
	return 1;
}


stock randomEx (min, max)
{
	return random((max - min + 1)) + min;
}


stock IsValidEmailAddress(const address[])
{
    new Regex:r = Regex_New("[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\\.[a-zA-Z0-9-.]+");
    new check = Regex_Check(address, r);
    
    Regex_Delete(r);
    return check;
}


stock ProxDetector(playerid, Float:max_range, color, const string[], GLOBAL_TAG_TYPES:...)
{
	new
		Float:pos_x,
		Float:pos_y,
		Float:pos_z,
		Float:range,
		Float:range_ratio,
		Float:range_with_ratio,
		clr_r, clr_g, clr_b,
		Float:color_r, Float:color_g, Float:color_b;

	if (!GetPlayerPos(playerid, pos_x, pos_y, pos_z)) {
		return 0;
	}

	color_r = float(color >> 24 & 0xFF);
	color_g = float(color >> 16 & 0xFF);
	color_b = float(color >> 8 & 0xFF);
	range_with_ratio = max_range * 1.6;

	if(numargs() > 4) {
		new out[145];
		va_format(out, 145, string, ___(4));

		foreach (new i : Player) {
			if (!IsPlayerStreamedIn(i, playerid)) {
				continue;
			}

			range = GetPlayerDistanceFromPoint(i, pos_x, pos_y, pos_z);
			if (range > max_range) {
				continue;
			}

			range_ratio = (range_with_ratio - range) / range_with_ratio;
			clr_r = floatround(range_ratio * color_r);
			clr_g = floatround(range_ratio * color_g);
			clr_b = floatround(range_ratio * color_b);

			SendClientMessage(i, (color & 0xFF) | (clr_b << 8) | (clr_g << 16) | (clr_r << 24), out);
		}
		SendClientMessage(playerid, color, out);
	} else {
		foreach (new i : Player) {
			if (!IsPlayerStreamedIn(i, playerid)) {
				continue;
			}

			range = GetPlayerDistanceFromPoint(i, pos_x, pos_y, pos_z);
			if (range > max_range) {
				continue;
			}

			range_ratio = (range_with_ratio - range) / range_with_ratio;
			clr_r = floatround(range_ratio * color_r);
			clr_g = floatround(range_ratio * color_g);
			clr_b = floatround(range_ratio * color_b);

			SendClientMessage(i, (color & 0xFF) | (clr_b << 8) | (clr_g << 16) | (clr_r << 24), string);
		}
		SendClientMessage(playerid, color, string);
	}
	return 1;
}


stock GivePlayerHealth(const playerid, Float:health)
{
	static Float:curr_health;
	GetPlayerHealth(playerid, curr_health);

	return SetPlayerHealth(playerid, (curr_health + health));
}


stock TextDrawSetStringEx(Text:text, const string[], {Float,_}:...)
{
	return TextDrawSetString(Text:text, va_return(string, ___(2)));
}

stock Dialog_ShowCallbackF(const playerid, Func:callback<iiiis>, style, const string:title[], const string:caption[], const string:button1[], const string:button2[] = "", {Float,_}:...)
{
	static string[4096];

	va_format(string, sizeof string, caption, ___(7));
	Dialog_ShowCallback(playerid, callback, style, title, string, button1, button2);
	return 1;
}