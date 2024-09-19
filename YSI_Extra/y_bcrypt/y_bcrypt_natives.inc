#if defined _INC_y_bcrypt_natives
	#endinput
#endif
#define _INC_y_bcrypt_natives

/*
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 the "License"; you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the YSI framework.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (c) 2022
	the Initial Developer. All Rights Reserved.

Contributors:
	Y_Less
	koolk
	JoeBullet/Google63
	g_aSlice/Slice
	Misiur
	samphunter
	tianmeta
	maddinat0r
	spacemud
	Crayder
	Dayvison
	Ahmad45123
	Zeex
	irinel1996
	Yiin-
	Chaprnks
	Konstantinos
	Masterchen09
	Southclaws
	PatchwerkQWER
	m0k1
	paulommu
	udan111
	Cheaterman

Thanks:
	JoeBullet/Google63 - Handy arbitrary ASM jump code using SCTRL.
	ZeeX - Very productive conversations.
	koolk - IsPlayerinAreaEx code.
	TheAlpha - Danish translation.
	breadfish - German translation.
	Fireburn - Dutch translation.
	yom - French translation.
	50p - Polish translation.
	Zamaroht - Spanish translation.
	Los - Portuguese translation.
	Dracoblue, sintax, mabako, Xtreme, other coders - Producing other modes for
		me to strive to better.
	Pixels^ - Running XScripters where the idea was born.
	Matite - Pestering me to release it and using it.

Very special thanks to:
	Thiadmer - PAWN, whose limits continue to amaze me!
	Kye/Kalcor - SA:MP.
	SA:MP Team past, present and future - SA:MP.

Optional plugins:
	Gamer_Z - GPS.
	Incognito - Streamer.
	Me - sscanf2, fixes2, Whirlpool.
*/

#include "..\..\YSI_Server\y_natives"
#include "..\..\YSI_Server\y_serverdata"

enum E_BCRYPT_PLUGIN_VERSION
{
	BCRYPT_PLUGIN_VERSION_NONE = -1,
	BCRYPT_PLUGIN_VERSION_UNKNOWN,
	BCRYPT_PLUGIN_VERSION_LASSIR, // A
	BCRYPT_PLUGIN_VERSION_SREYAS, // B
}

// Unify 2 BCrypt plugins in to a single API.
stock
	_YSI_gHashID = 0,
	_YSI_gLastHash = 0;

// Lassir
@native("bcrypt_get_hash", .print = false) bool:_YSI_BCryptGetHashA(hash[]);
@native("bcrypt_check", .print = false) bool:_YSI_BCryptCheckA(const password[], const hash[], const callback[], const args[], GLOBAL_TAG_TYPES:...);
@native("bcrypt_hash", .print = false) bool:_YSI_BCryptHashA(const password[], cost, const callback[], const args[], GLOBAL_TAG_TYPES:...);
@native("bcrypt_is_equal", .print = false) bool:_YSI_BCryptIsEqualA();

// SyS
@native("bcrypt_get_hash", .print = false) bool:_YSI_BCryptGetHashB(hash[], size);
@native("bcrypt_verify", .print = false) bool:_YSI_BCryptCheckB(extra, const callback[], const password[], const hash[], const args[], GLOBAL_TAG_TYPES:...);
@native("bcrypt_hash", .print = false) bool:_YSI_BCryptHashB(extra, const callback[], const password[], cost, const args[], GLOBAL_TAG_TYPES:...);
@native("bcrypt_set_thread_limit", .print = false) bool:_YSI_BCryptSetThreadLimitB(limit);

static stock
	E_BCRYPT_PLUGIN_VERSION:YSI_g_sBCryptPlugin = BCRYPT_PLUGIN_VERSION_NONE;

stock BCrypt_SetPlugin(E_BCRYPT_PLUGIN_VERSION:plugin)
{
	YSI_g_sBCryptPlugin = plugin;
}

stock E_BCRYPT_PLUGIN_VERSION:BCrypt_GetPlugin()
{
	if (YSI_g_sBCryptPlugin == BCRYPT_PLUGIN_VERSION_NONE)
	{
		if (Server_HasNative("bcrypt_is_equal"))
		{
			YSI_g_sBCryptPlugin = BCRYPT_PLUGIN_VERSION_LASSIR;
		}
		else if (Server_HasNative("bcrypt_set_thread_limit"))
		{
			YSI_g_sBCryptPlugin = BCRYPT_PLUGIN_VERSION_SREYAS;
		}
		else
		{
			Debug_Error("No known BCrypt plugin is loaded.  Load Lassir or Sreyas-Sreelal!");
			YSI_g_sBCryptPlugin = BCRYPT_PLUGIN_VERSION_UNKNOWN;
		}
	}
	return YSI_g_sBCryptPlugin;
}
