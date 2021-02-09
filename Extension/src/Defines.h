#pragma once

#define MAXPLAYERS      65  /**< Maximum number of players SourceMod supports */
#define MAX_NAME_LENGTH 128 /**< Maximum buffer required to store a client name */

#define ADMFLAG_RESERVATION			(1<<0)		/**< Convenience macro for Admin_Reservation as a FlagBit */
#define ADMFLAG_GENERIC				(1<<1)		/**< Convenience macro for Admin_Generic as a FlagBit */
#define ADMFLAG_KICK				(1<<2)		/**< Convenience macro for Admin_Kick as a FlagBit */
#define ADMFLAG_BAN					(1<<3)		/**< Convenience macro for Admin_Ban as a FlagBit */
#define ADMFLAG_UNBAN				(1<<4)		/**< Convenience macro for Admin_Unban as a FlagBit */
#define ADMFLAG_SLAY				(1<<5)		/**< Convenience macro for Admin_Slay as a FlagBit */
#define ADMFLAG_CHANGEMAP			(1<<6)		/**< Convenience macro for Admin_Changemap as a FlagBit */
#define ADMFLAG_CONVARS				(1<<7)		/**< Convenience macro for Admin_Convars as a FlagBit */
#define ADMFLAG_CONFIG				(1<<8)		/**< Convenience macro for Admin_Config as a FlagBit */
#define ADMFLAG_CHAT				(1<<9)		/**< Convenience macro for Admin_Chat as a FlagBit */
#define ADMFLAG_VOTE				(1<<10)		/**< Convenience macro for Admin_Vote as a FlagBit */
#define ADMFLAG_PASSWORD			(1<<11)		/**< Convenience macro for Admin_Password as a FlagBit */
#define ADMFLAG_RCON				(1<<12)		/**< Convenience macro for Admin_RCON as a FlagBit */
#define ADMFLAG_CHEATS				(1<<13)		/**< Convenience macro for Admin_Cheats as a FlagBit */
#define ADMFLAG_ROOT				(1<<14)		/**< Convenience macro for Admin_Root as a FlagBit */
#define ADMFLAG_CUSTOM1				(1<<15)		/**< Convenience macro for Admin_Custom1 as a FlagBit */
#define ADMFLAG_CUSTOM2				(1<<16)		/**< Convenience macro for Admin_Custom2 as a FlagBit */
#define ADMFLAG_CUSTOM3				(1<<17)		/**< Convenience macro for Admin_Custom3 as a FlagBit */
#define ADMFLAG_CUSTOM4				(1<<18)		/**< Convenience macro for Admin_Custom4 as a FlagBit */
#define ADMFLAG_CUSTOM5				(1<<19)		/**< Convenience macro for Admin_Custom5 as a FlagBit */
#define ADMFLAG_CUSTOM6				(1<<20)		/**< Convenience macro for Admin_Custom6 as a FlagBit */

#define AUTHMETHOD_STEAM            "steam"     /**< SteamID based authentication */
#define AUTHMETHOD_IP               "ip"        /**< IP based authentication */
#define AUTHMETHOD_NAME             "name"      /**< Name based authentication */

#define INVALID_HANDLE 0

static constexpr float NULL_VECTOR[] = { 0.0f, 0.0f, 0.0f };
static int NULL_VALUE = 0;

using Handle = int;
using EventHandle = int;

enum UseType
{
	Use_Off,
	Use_On,
	Use_Set,
	Use_Toggle
};

/**
 * Event hook modes determining how hooking should be handled
 */
enum EventHookMode
{
	EventHookMode_Pre,                  //< Hook callback fired before event is fired */
	EventHookMode_Post,                 //< Hook callback fired after event is fired */
	EventHookMode_PostNoCopy            //< Hook callback fired after event is fired, but event data won't be copied */
};

/*
enum OverrideType
{
	Override_Command = 1,   // Command
	Override_CommandGroup   // Command group
};

enum OverrideRule
{
	Command_Deny = 0,
	Command_Allow = 1
};

enum GroupId
{
	INVALID_GROUP_ID = -1   // An invalid/non-existent group
};

enum AdminId
{
	INVALID_ADMIN_ID = -1   // An invalid/non-existent admin
};

enum AdmAccessMode
{
	Access_Real,        // Access the user has inherently
	Access_Effective    // Access the user has from their groups
};

enum AdminCachePart
{
	AdminCache_Overrides = 0,      // Global overrides
	AdminCache_Groups = 1,         // All groups (automatically invalidates admins too)
	AdminCache_Admins = 2          // All admins
};
*/

/*enum AdminFlag
{
	Admin_Reservation, // Reserved slot
	Admin_Generic,     // Generic admin abilities
	Admin_Kick,        // Kick another user
	Admin_Ban,         // Ban another user
	Admin_Unban,       // Unban another user
	Admin_Slay,        // Slay/kill/damage another user
	Admin_Changemap,   // Change the map
	Admin_Convars,     // Change basic convars
	Admin_Config,      // Change configuration
	Admin_Chat,        // Special chat privileges
	Admin_Vote,        // Special vote privileges
	Admin_Password,    // Set a server password
	Admin_RCON,        // Use RCON
	Admin_Cheats,      // Change sv_cheats and use its commands
	Admin_Root,        // All access by default
	Admin_Custom1,     // First custom flag type
	Admin_Custom2,     // Second custom flag type
	Admin_Custom3,     // Third custom flag type
	Admin_Custom4,     // Fourth custom flag type
	Admin_Custom5,     // Fifth custom flag type
	Admin_Custom6      // Sixth custom flag type
};*/

enum NetFlow
{
	NetFlow_Outgoing = 0,   // Outgoing traffic
	NetFlow_Incoming,       // Incoming traffic
	NetFlow_Both            // Both values added together
};

enum AuthIdType
{
	AuthId_Engine = 0,     // The game-specific auth string as returned from the engine

	// The following are only available on games that support Steam authentication.
	AuthId_Steam2,         // Steam2 rendered format, ex "STEAM_1:1:4153990"
	AuthId_Steam3,         // Steam3 rendered format, ex "[U:1:8307981]"
	AuthId_SteamID64       // A SteamID64 (uint64) as a String, ex "76561197968573709"
};

#define INVALID_FCVAR_FLAGS (-1)

/**
 * Console variable query helper values.
 */
enum QueryCookie
{
	QUERYCOOKIE_FAILED = 0
};

/**
 * Reply sources for commands.
 */
enum ReplySource
{
	SM_REPLY_TO_CONSOLE = 0,
	SM_REPLY_TO_CHAT = 1
};

#define FCVAR_PLUGIN           0       // Actual value is same as FCVAR_SS_ADDED in Left 4 Dead and later.

#define FCVAR_NONE                      0      // The default, no flags at all
#define FCVAR_UNREGISTERED             (1<<0)  // If this is set, don't add to linked list, etc.
#define FCVAR_DEVELOPMENTONLY          (1<<1)  // Hidden in released products. Flag is removed automatically if ALLOW_DEVELOPMENT_CVARS is defined. (OB+)
#define FCVAR_GAMEDLL                  (1<<2)  // Defined by the game DLL.
#define FCVAR_CLIENTDLL                (1<<3)  // Defined by the client DLL.
#define FCVAR_MATERIAL_SYSTEM          (1<<4)  // Defined by the material system. (EP1-only)
#define FCVAR_HIDDEN                   (1<<4)  // Hidden. Doesn't appear in find or autocomplete. Like DEVELOPMENTONLY, but can't be compiled out.1 (OB+)
#define FCVAR_PROTECTED                (1<<5)  // It's a server cvar, but we don't send the data since it's a password, etc.
 // Sends 1 if it's not bland/zero, 0 otherwise as value.
#define FCVAR_SPONLY                   (1<<6)  // This cvar cannot be changed by clients connected to a multiplayer server.
#define FCVAR_ARCHIVE                  (1<<7)  // Set to cause it to be saved to vars.rc
#define FCVAR_NOTIFY                   (1<<8)  // Notifies players when changed.
#define FCVAR_USERINFO                 (1<<9)  // Changes the client's info string.
#define FCVAR_PRINTABLEONLY            (1<<10) // This cvar's string cannot contain unprintable characters (e.g., used for player name, etc.)
#define FCVAR_UNLOGGED                 (1<<11) // If this is a FCVAR_SERVER, don't log changes to the log file / console if we are creating a log
#define FCVAR_NEVER_AS_STRING          (1<<12) // Never try to print that cvar.
#define FCVAR_REPLICATED               (1<<13) // Server setting enforced on clients.
#define FCVAR_CHEAT                    (1<<14) // Only useable in singleplayer / debug / multiplayer & sv_cheats
#define FCVAR_SS                       (1<<15) // causes varnameN where N  2 through max splitscreen slots for mod to be autogenerated (L4D+)
#define FCVAR_DEMO                     (1<<16) // Record this cvar when starting a demo file.
#define FCVAR_DONTRECORD               (1<<17) // Don't record these command in demo files.
#define FCVAR_SS_ADDED                 (1<<18) // This is one of the "added" FCVAR_SS variables for the splitscreen players (L4D+)
#define FCVAR_RELEASE                  (1<<19) // Cvars tagged with this are the only cvars available to customers (L4D+)
#define FCVAR_RELOAD_MATERIALS         (1<<20) // If this cvar changes, it forces a material reload (OB+)
#define FCVAR_RELOAD_TEXTURES          (1<<21) // If this cvar changes, if forces a texture reload (OB+)
#define FCVAR_NOT_CONNECTED            (1<<22) // Cvar cannot be changed by a client that is connected to a server.
#define FCVAR_MATERIAL_SYSTEM_THREAD   (1<<23) // Indicates this cvar is read from the material system thread (OB+)
#define FCVAR_ARCHIVE_XBOX             (1<<24) // Cvar written to config.cfg on the Xbox.
#define FCVAR_ARCHIVE_GAMECONSOLE      (1<<24) // Cvar written to config.cfg on the Xbox.
#define FCVAR_ACCESSIBLE_FROM_THREADS  (1<<25) // used as a debugging tool necessary to check material system thread convars (OB+)
#define FCVAR_SERVER_CAN_EXECUTE       (1<<28) // the server is allowed to execute this command on clients via
                                               // ClientCommand/NET_StringCmd/CBaseClientState::ProcessStringCmd. (OB+)
#define FCVAR_SERVER_CANNOT_QUERY      (1<<29) // If this is set, then the server is not allowed to query this cvar's value (via
                                               // IServerPluginHelpers::StartQueryCvarValue).
#define FCVAR_CLIENTCMD_CAN_EXECUTE    (1<<30) // IVEngineClient::ClientCmd is allowed to execute this command.
                                               // Note: IVEngineClient::ClientCmd_Unrestricted can run any client command.


#define CS_TEAM_NONE        0   /**< No team yet. */
#define CS_TEAM_SPECTATOR   1   /**< Spectators. */
#define CS_TEAM_T           2   /**< Terrorists. */
#define CS_TEAM_CT          3   /**< Counter-Terrorists. */

#define CS_SLOT_PRIMARY     0   /**< Primary weapon slot. */
#define CS_SLOT_SECONDARY   1   /**< Secondary weapon slot. */
#define CS_SLOT_KNIFE       2   /**< Knife slot. */
#define CS_SLOT_GRENADE     3   /**< Grenade slot (will only return one grenade). */
#define CS_SLOT_C4          4   /**< C4 slot. */
#define CS_SLOT_BOOST       11  /**< Slot for healthshot and shield (will only return one weapon/item). */
#define CS_SLOT_UTILITY     12  /**< Slot for tablet. */

#define CS_DMG_HEADSHOT     (1 << 30)    /**< Headshot */

// SDKHOOKS.INC
#define DMG_GENERIC                  0          /**< generic damage was done */
#define DMG_CRUSH                   (1 << 0)    /**< crushed by falling or moving object.
													 NOTE: It's assumed crush damage is occurring as a result of physics collision,
													 so no extra physics force is generated by crush damage.
													 DON'T use DMG_CRUSH when damaging entities unless it's the result of a physics
													 collision. You probably want DMG_CLUB instead. */
#define DMG_BULLET                  (1 << 1)    /**< shot */
#define DMG_SLASH                   (1 << 2)    /**< cut, clawed, stabbed */
#define DMG_BURN                    (1 << 3)    /**< heat burned */
#define DMG_VEHICLE                 (1 << 4)    /**< hit by a vehicle */
#define DMG_FALL                    (1 << 5)    /**< fell too far */
#define DMG_BLAST                   (1 << 6)    /**< explosive blast damage */
#define DMG_CLUB                    (1 << 7)    /**< crowbar, punch, headbutt */
#define DMG_SHOCK                   (1 << 8)    /**< electric shock */
#define DMG_SONIC                   (1 << 9)    /**< sound pulse shockwave */
#define DMG_ENERGYBEAM              (1 << 10)   /**< laser or other high energy beam  */
#define DMG_PREVENT_PHYSICS_FORCE   (1 << 11)   /**< Prevent a physics force  */
#define DMG_NEVERGIB                (1 << 12)   /**< with this bit OR'd in, no damage type will be able to gib victims upon death */
#define DMG_ALWAYSGIB               (1 << 13)   /**< with this bit OR'd in, any damage type can be made to gib victims upon death. */
#define DMG_DROWN                   (1 << 14)   /**< Drowning */
#define DMG_PARALYZE                (1 << 15)   /**< slows affected creature down */
#define DMG_NERVEGAS                (1 << 16)   /**< nerve toxins, very bad */
#define DMG_POISON                  (1 << 17)   /**< blood poisoning - heals over time like drowning damage */
#define DMG_RADIATION               (1 << 18)   /**< radiation exposure */
#define DMG_DROWNRECOVER            (1 << 19)   /**< drowning recovery */
#define DMG_ACID                    (1 << 20)   /**< toxic chemicals or acid burns */
#define DMG_SLOWBURN                (1 << 21)   /**< in an oven */
#define DMG_REMOVENORAGDOLL         (1 << 22)   /**< with this bit OR'd in, no ragdoll will be created, and the target will be quietly removed.
													 use this to kill an entity that you've already got a server-side ragdoll for */
#define DMG_PHYSGUN                 (1 << 23)   /**< Hit by manipulator. Usually doesn't do any damage. */
#define DMG_PLASMA                  (1 << 24)   /**< Shot by Cremator */
#define DMG_AIRBOAT                 (1 << 25)   /**< Hit by the airboat's gun */
#define DMG_DISSOLVE                (1 << 26)   /**< Dissolving! */
#define DMG_BLAST_SURFACE           (1 << 27)   /**< A blast on the surface of water that cannot harm things underwater */
#define DMG_DIRECT                  (1 << 28)
#define DMG_BUCKSHOT                (1 << 29)   /**< not quite a bullet. Little, rounder, different. */

enum SDKHookType
{
	SDKHook_EndTouch,
	SDKHook_FireBulletsPost,
	SDKHook_OnTakeDamage,
	SDKHook_OnTakeDamagePost,
	SDKHook_PreThink,
	SDKHook_PostThink,
	SDKHook_SetTransmit,
	SDKHook_Spawn,
	SDKHook_StartTouch,
	SDKHook_Think,
	SDKHook_Touch,
	SDKHook_TraceAttack,
	SDKHook_TraceAttackPost,
	SDKHook_WeaponCanSwitchTo,
	SDKHook_WeaponCanUse,
	SDKHook_WeaponDrop,
	SDKHook_WeaponEquip,
	SDKHook_WeaponSwitch,
	SDKHook_ShouldCollide,
	SDKHook_PreThinkPost,
	SDKHook_PostThinkPost,
	SDKHook_ThinkPost,
	SDKHook_EndTouchPost,
	SDKHook_GroundEntChangedPost,
	SDKHook_SpawnPost,
	SDKHook_StartTouchPost,
	SDKHook_TouchPost,
	SDKHook_VPhysicsUpdate,
	SDKHook_VPhysicsUpdatePost,
	SDKHook_WeaponCanSwitchToPost,
	SDKHook_WeaponCanUsePost,
	SDKHook_WeaponDropPost,
	SDKHook_WeaponEquipPost,
	SDKHook_WeaponSwitchPost,
	SDKHook_Use,
	SDKHook_UsePost,
	SDKHook_Reload,
	SDKHook_ReloadPost,
	SDKHook_GetMaxHealth,  /**< ep2v and later */
	SDKHook_Blocked,
	SDKHook_BlockedPost,
	SDKHook_OnTakeDamageAlive,
	SDKHook_OnTakeDamageAlivePost,
	SDKHook_CanBeAutobalanced
};


using KeyValuesHandle = int;

enum CSRoundEndReason
{
	CSRoundEnd_TargetBombed = 0,           /**< Target Successfully Bombed! */
	CSRoundEnd_VIPEscaped,                 /**< The VIP has escaped! - Doesn't exist on CS:GO */
	CSRoundEnd_VIPKilled,                  /**< VIP has been assassinated! - Doesn't exist on CS:GO */
	CSRoundEnd_TerroristsEscaped,          /**< The terrorists have escaped! */
	CSRoundEnd_CTStoppedEscape,            /**< The CTs have prevented most of the terrorists from escaping! */
	CSRoundEnd_TerroristsStopped,          /**< Escaping terrorists have all been neutralized! */
	CSRoundEnd_BombDefused,                /**< The bomb has been defused! */
	CSRoundEnd_CTWin,                      /**< Counter-Terrorists Win! */
	CSRoundEnd_TerroristWin,               /**< Terrorists Win! */
	CSRoundEnd_Draw,                       /**< Round Draw! */
	CSRoundEnd_HostagesRescued,            /**< All Hostages have been rescued! */
	CSRoundEnd_TargetSaved,                /**< Target has been saved! */
	CSRoundEnd_HostagesNotRescued,         /**< Hostages have not been rescued! */
	CSRoundEnd_TerroristsNotEscaped,       /**< Terrorists have not escaped! */
	CSRoundEnd_VIPNotEscaped,              /**< VIP has not escaped! - Doesn't exist on CS:GO */
	CSRoundEnd_GameStart,                  /**< Game Commencing! */

	// The below only exist on CS:GO
	CSRoundEnd_TerroristsSurrender,        /**< Terrorists Surrender */
	CSRoundEnd_CTSurrender,                /**< CTs Surrender */
	CSRoundEnd_TerroristsPlanted,          /**< Terrorists Planted the bomb */
	CSRoundEnd_CTsReachedHostage           /**< CTs Reached the hostage */
};

enum CSWeaponID
{
	CSWeapon_NONE = 0,
	CSWeapon_P228,
	CSWeapon_GLOCK,
	CSWeapon_SCOUT,
	CSWeapon_HEGRENADE,
	CSWeapon_XM1014,
	CSWeapon_C4,
	CSWeapon_MAC10,
	CSWeapon_AUG,
	CSWeapon_SMOKEGRENADE,
	CSWeapon_ELITE,
	CSWeapon_FIVESEVEN,
	CSWeapon_UMP45,
	CSWeapon_SG550,
	CSWeapon_GALIL,
	CSWeapon_FAMAS,
	CSWeapon_USP,
	CSWeapon_AWP,
	CSWeapon_MP5NAVY,
	CSWeapon_M249,
	CSWeapon_M3,
	CSWeapon_M4A1,
	CSWeapon_TMP,
	CSWeapon_G3SG1,
	CSWeapon_FLASHBANG,
	CSWeapon_DEAGLE,
	CSWeapon_SG552,
	CSWeapon_AK47,
	CSWeapon_KNIFE,
	CSWeapon_P90,
	CSWeapon_SHIELD,
	CSWeapon_KEVLAR,
	CSWeapon_ASSAULTSUIT,
	CSWeapon_NIGHTVISION, //Anything below is CS:GO ONLY
	CSWeapon_GALILAR,
	CSWeapon_BIZON,
	CSWeapon_MAG7,
	CSWeapon_NEGEV,
	CSWeapon_SAWEDOFF,
	CSWeapon_TEC9,
	CSWeapon_TASER,
	CSWeapon_HKP2000,
	CSWeapon_MP7,
	CSWeapon_MP9,
	CSWeapon_NOVA,
	CSWeapon_P250,
	CSWeapon_SCAR17,
	CSWeapon_SCAR20,
	CSWeapon_SG556,
	CSWeapon_SSG08,
	CSWeapon_KNIFE_GG,
	CSWeapon_MOLOTOV,
	CSWeapon_DECOY,
	CSWeapon_INCGRENADE,
	CSWeapon_DEFUSER,
	CSWeapon_HEAVYASSAULTSUIT,
	//The rest are actual item definition indexes for CS:GO
	CSWeapon_CUTTERS = 56,
	CSWeapon_HEALTHSHOT = 57,
	CSWeapon_KNIFE_T = 59,
	CSWeapon_M4A1_SILENCER = 60,
	CSWeapon_USP_SILENCER = 61,
	CSWeapon_CZ75A = 63,
	CSWeapon_REVOLVER = 64,
	CSWeapon_TAGGRENADE = 68,
	CSWeapon_FISTS = 69,
	CSWeapon_BREACHCHARGE = 70,
	CSWeapon_TABLET = 72,
	CSWeapon_MELEE = 74,
	CSWeapon_AXE = 75,
	CSWeapon_HAMMER = 76,
	CSWeapon_SPANNER = 78,
	CSWeapon_KNIFE_GHOST = 80,
	CSWeapon_FIREBOMB = 81,
	CSWeapon_DIVERSION = 82,
	CSWeapon_FRAGGRENADE = 83,
	CSWeapon_SNOWBALL = 84,
	CSWeapon_BUMPMINE = 85,
	CSWeapon_MAX_WEAPONS_NO_KNIFES, // Max without the knife item defs, useful when treating all knives as a regular knife.
	CSWeapon_BAYONET = 500,
	CSWeapon_KNIFE_CLASSIC = 503,
	CSWeapon_KNIFE_FLIP = 505,
	CSWeapon_KNIFE_GUT = 506,
	CSWeapon_KNIFE_KARAMBIT = 507,
	CSWeapon_KNIFE_M9_BAYONET = 508,
	CSWeapon_KNIFE_TATICAL = 509,
	CSWeapon_KNIFE_FALCHION = 512,
	CSWeapon_KNIFE_SURVIVAL_BOWIE = 514,
	CSWeapon_KNIFE_BUTTERFLY = 515,
	CSWeapon_KNIFE_PUSH = 516,
	CSWeapon_KNIFE_CORD = 517,
	CSWeapon_KNIFE_CANIS = 518,
	CSWeapon_KNIFE_URSUS = 519,
	CSWeapon_KNIFE_GYPSY_JACKKNIFE = 520,
	CSWeapon_KNIFE_OUTDOOR = 521,
	CSWeapon_KNIFE_STILETTO = 522,
	CSWeapon_KNIFE_WIDOWMAKER = 523,
	CSWeapon_KNIFE_SKELETON = 525,
	CSWeapon_MAX_WEAPONS //THIS MUST BE LAST, EASY WAY TO CREATE LOOPS. When looping, do CS_IsValidWeaponID(i), to check.
};

/**
 * Describes a database field fetch status.
 */
enum DBResult
{
	DBVal_Error = 0,        /**< Column number/field is invalid. */
	DBVal_TypeMismatch = 1, /**< You cannot retrieve this data with this type. */
	DBVal_Null = 2,         /**< Field has no data (NULL) */
	DBVal_Data = 3          /**< Field has data */
};

/**
 * Describes binding types.
 */
enum DBBindType
{
	DBBind_Int = 0,         /**< Bind an integer. */
	DBBind_Float = 1,       /**< Bind a float. */
	DBBind_String = 2       /**< Bind a string. */
};

/**
 * Threading priority level.
 */
enum DBPriority
{
	DBPrio_High = 0,        /**< High priority. */
	DBPrio_Normal = 1,      /**< Normal priority. */
	DBPrio_Low = 2          /**< Low priority. */
};

using database_t = int;
using transaction_t = int;
using DBResultSet = int;
using DBDriver = int;
using DBStatement = int;
using KeyValuesHandle = int;

/**
 * Low-level drawing style of the menu.
 */
enum MenuStyle
{
	MenuStyle_Default = 0,      /**< The "default" menu style for the mod */
	MenuStyle_Valve = 1,        /**< The Valve provided menu style (Used on HL2DM) */
	MenuStyle_Radio = 2         /**< The simpler menu style commonly used on CS:S */
};

/**
 * Different actions for the menu "pump" callback
 */
enum MenuAction
{
	MenuAction_Start = (1 << 0),      /**< A menu has been started (nothing passed) */
	MenuAction_Display = (1 << 1),    /**< A menu is about to be displayed (param1=client, param2=MenuPanel Handle) */
	MenuAction_Select = (1 << 2),     /**< An item was selected (param1=client, param2=item) */
	MenuAction_Cancel = (1 << 3),     /**< The menu was cancelled (param1=client, param2=reason) */
	MenuAction_End = (1 << 4),        /**< A menu display has fully ended.
                                           param1 is the MenuEnd reason, and if it's MenuEnd_Cancelled, then
                                           param2 is the MenuCancel reason from MenuAction_Cancel. */
	MenuAction_VoteEnd = (1 << 5),    /**< (VOTE ONLY): A vote sequence has succeeded (param1=chosen item)
                                            This is not called if SetVoteResultCallback has been used on the menu. */
	MenuAction_VoteStart = (1 << 6),  /**< (VOTE ONLY): A vote sequence has started (nothing passed) */
	MenuAction_VoteCancel = (1 << 7), /**< (VOTE ONLY): A vote sequence has been cancelled (param1=reason) */
	MenuAction_DrawItem = (1 << 8),   /**< An item is being drawn; return the new style (param1=client, param2=item) */
	MenuAction_DisplayItem = (1 << 9) /**< Item text is being drawn to the display (param1=client, param2=item)
										   To change the text, use RedrawMenuItem().
										   If you do so, return its return value.  Otherwise, return 0. */
};

/** Default menu actions */
#define MENU_ACTIONS_DEFAULT    static_cast<MenuAction>(MenuAction_Select | MenuAction_Cancel | MenuAction_End)
/** All menu actions */
#define MENU_ACTIONS_ALL        static_cast<MenuAction>(0xFFFFFFFF)

#define MENU_NO_PAGINATION      0           /**< Menu should not be paginated (10 items max) */
#define MENU_TIME_FOREVER       0           /**< Menu should be displayed as long as possible */

#define ITEMDRAW_DEFAULT            (0)     /**< Item should be drawn normally */
#define ITEMDRAW_DISABLED           (1<<0)  /**< Item is drawn but not selectable */
#define ITEMDRAW_RAWLINE            (1<<1)  /**< Item should be a raw line, without a slot */
#define ITEMDRAW_NOTEXT             (1<<2)  /**< No text should be drawn */
#define ITEMDRAW_SPACER             (1<<3)  /**< Item should be drawn as a spacer, if possible */
#define ITEMDRAW_IGNORE     ((1<<1)|(1<<2)) /**< Item should be completely ignored (rawline + notext) */
#define ITEMDRAW_CONTROL            (1<<4)  /**< Item is control text (back/next/exit) */

#define MENUFLAG_BUTTON_EXIT        (1<<0)  /**< Menu has an "exit" button (default if paginated) */
#define MENUFLAG_BUTTON_EXITBACK    (1<<1)  /**< Menu has an "exit back" button */
#define MENUFLAG_NO_SOUND           (1<<2)  /**< Menu will not have any select sounds */
#define MENUFLAG_BUTTON_NOVOTE      (1<<3)  /**< Menu has a "No Vote" button at slot 1 */

#define VOTEINFO_CLIENT_INDEX       0       /**< Client index */
#define VOTEINFO_CLIENT_ITEM        1       /**< Item the client selected, or -1 for none */
#define VOTEINFO_ITEM_INDEX         0       /**< Item index */
#define VOTEINFO_ITEM_VOTES         1       /**< Number of votes for the item */

#define VOTEFLAG_NO_REVOTES         (1<<0)  /**< Players cannot change their votes */

/**
 * Reasons a menu can be cancelled (MenuAction_Cancel).
 */
enum
{
	MenuCancel_Disconnected = -1,   /**< Client dropped from the server */
	MenuCancel_Interrupted = -2,    /**< Client was interrupted with another menu */
	MenuCancel_Exit = -3,           /**< Client exited via "exit" */
	MenuCancel_NoDisplay = -4,      /**< Menu could not be displayed to the client */
	MenuCancel_Timeout = -5,        /**< Menu timed out */
	MenuCancel_ExitBack = -6        /**< Client selected "exit back" on a paginated menu */
};

/**
 * Reasons a vote can be cancelled (MenuAction_VoteCancel).
 */
enum
{
	VoteCancel_Generic = -1,        /**< Vote was generically cancelled. */
	VoteCancel_NoVotes = -2         /**< Vote did not receive any votes. */
};

/**
 * Reasons a menu ended (MenuAction_End).
 */
enum
{
	MenuEnd_Selected = 0,           /**< Menu item was selected */
	MenuEnd_VotingDone = -1,        /**< Voting finished */
	MenuEnd_VotingCancelled = -2,   /**< Voting was cancelled */
	MenuEnd_Cancelled = -3,         /**< Menu was cancelled (reason in param2) */
	MenuEnd_Exit = -4,              /**< Menu was cleanly exited via "exit" */
	MenuEnd_ExitBack = -5           /**< Menu was cleanly exited via "back" */
};

/**
 * Describes a menu's source
 */
enum MenuSource
{
	MenuSource_None = 0,            /**< No menu is being displayed */
	MenuSource_External = 1,        /**< External menu */
	MenuSource_Normal = 2,          /**< A basic menu is being displayed */
	MenuSource_RawPanel = 3         /**< A display is active, but it is not tied to a menu */
};

using MenuHandle = int;
using PanelHandle = int;

// ENTITY.INC

enum PropType
{
	Prop_Send = 0,  /**< This property is networked. */
	Prop_Data = 1   /**< This property is for save game data fields. */
};

#define FL_EDICT_CHANGED                (1<<0)  /**< Game DLL sets this when the entity state changes
                                                     Mutually exclusive with FL_EDICT_PARTIAL_CHANGE. */
#define FL_EDICT_FREE                   (1<<1)  /**< this edict if free for reuse */
#define FL_EDICT_FULL                   (1<<2)  /**< this is a full server entity */
#define FL_EDICT_FULLCHECK              (0<<0)  /**< call ShouldTransmit() each time, this is a fake flag */
#define FL_EDICT_ALWAYS                 (1<<3)  /**< always transmit this entity */
#define FL_EDICT_DONTSEND               (1<<4)  /**< don't transmit this entity */
#define FL_EDICT_PVSCHECK               (1<<5)  /**< always transmit entity, but cull against PVS */
#define FL_EDICT_PENDING_DORMANT_CHECK  (1<<6)
#define FL_EDICT_DIRTY_PVS_INFORMATION  (1<<7)
#define FL_FULL_EDICT_CHANGED           (1<<8)

enum PropFieldType
{
	PropField_Unsupported,      /**< The type is unsupported. */
	PropField_Integer,          /**< Valid for SendProp and Data fields */
	PropField_Float,            /**< Valid for SendProp and Data fields */
	PropField_Entity,           /**< Valid for Data fields only (SendProp shows as int) */
	PropField_Vector,           /**< Valid for SendProp and Data fields */
	PropField_String,           /**< Valid for SendProp and Data fields */
	PropField_String_T,         /**< Valid for Data fields.  Read only.
                                     Note that the size of a string_t is dynamic, and
                                     thus FindDataMapOffs() will return the constant size
                                     of the string_t container (which is 32 bits right now). */
	PropField_Variant           /**< Valid for Data fields only Type is not known at the field level,
                                     (for this call), but dependent on current field value. */
};

// TIMERS.INC

#define TIMER_REPEAT            (1<<0)      /**< Timer will repeat until it returns Plugin_Stop */
#define TIMER_FLAG_NO_MAPCHANGE (1<<1)      /**< Timer will not carry over mapchanges */
#define TIMER_DATA_HNDL_CLOSE   (1<<9)      /**< Timer will automatically call CloseHandle() on its data when finished */

// HALFLIFE.INC

#define SOURCE_SDK_UNKNOWN           0      /**< Could not determine the engine version */
#define SOURCE_SDK_ORIGINAL         10      /**< Original Source engine (still used by "The Ship") */
#define SOURCE_SDK_DARKMESSIAH      15      /**< Modified version of original engine used by Dark Messiah (no SDK) */
#define SOURCE_SDK_EPISODE1         20      /**< SDK+Engine released after Episode 1 */
#define SOURCE_SDK_EPISODE2         30      /**< SDK+Engine released after Episode 2/Orange Box */
#define SOURCE_SDK_BLOODYGOODTIME   32      /**< Modified version of ep2 engine used by Bloody Good Time (no SDK) */
#define SOURCE_SDK_EYE              33      /**< Modified version of ep2 engine used by E.Y.E Divine Cybermancy (no SDK) */
#define SOURCE_SDK_CSS              34      /**< Sometime-older version of Source 2009 SDK+Engine, used for Counter-Strike: Source */
#define SOURCE_SDK_EPISODE2VALVE    35      /**< SDK+Engine released after Episode 2/Orange Box, "Source 2009" or "Source MP" */
#define SOURCE_SDK_LEFT4DEAD        40      /**< Engine released after Left 4 Dead (no SDK yet) */
#define SOURCE_SDK_LEFT4DEAD2       50      /**< Engine released after Left 4 Dead 2 (no SDK yet) */
#define SOURCE_SDK_ALIENSWARM       60      /**< SDK+Engine released after Alien Swarm */
#define SOURCE_SDK_CSGO             80      /**< Engine released after CS:GO (no SDK yet) */
#define SOURCE_SDK_DOTA             90      /**< Engine released after Dota 2 (no SDK) */

#define MOTDPANEL_TYPE_TEXT          0      /**< Treat msg as plain text */
#define MOTDPANEL_TYPE_INDEX         1      /**< Msg is auto determined by the engine */
#define MOTDPANEL_TYPE_URL           2      /**< Treat msg as an URL link */
#define MOTDPANEL_TYPE_FILE          3      /**< Treat msg as a filename to be opened */

enum DialogType
{
	DialogType_Msg = 0,     /**< just an on screen message */
	DialogType_Menu,        /**< an options menu */
	DialogType_Text,        /**< a richtext dialog */
	DialogType_Entry,       /**< an entry box */
	DialogType_AskConnect   /**< ask the client to connect to a specified IP */
};

enum EngineVersion
{
	Engine_Unknown,             /**< Could not determine the engine version */
	Engine_Original,            /**< Original Source Engine (used by The Ship) */
	Engine_SourceSDK2006,       /**< Episode 1 Source Engine (second major SDK) */
	Engine_SourceSDK2007,       /**< Orange Box Source Engine (third major SDK) */
	Engine_Left4Dead,           /**< Left 4 Dead */
	Engine_DarkMessiah,         /**< Dark Messiah Multiplayer (based on original engine) */
	Engine_Left4Dead2 = 7,      /**< Left 4 Dead 2 */
	Engine_AlienSwarm,          /**< Alien Swarm (and Alien Swarm SDK) */
	Engine_BloodyGoodTime,      /**< Bloody Good Time */
	Engine_EYE,                 /**< E.Y.E Divine Cybermancy */
	Engine_Portal2,             /**< Portal 2 */
	Engine_CSGO,                /**< Counter-Strike: Global Offensive */
	Engine_CSS,                 /**< Counter-Strike: Source */
	Engine_DOTA,                /**< Dota 2 */
	Engine_HL2DM,               /**< Half-Life 2 Deathmatch */
	Engine_DODS,                /**< Day of Defeat: Source */
	Engine_TF2,                 /**< Team Fortress 2 */
	Engine_NuclearDawn,         /**< Nuclear Dawn */
	Engine_SDK2013,             /**< Source SDK 2013 */
	Engine_Blade,               /**< Blade Symphony */
	Engine_Insurgency,          /**< Insurgency (2013 Retail version)*/
	Engine_Contagion,           /**< Contagion */
	Engine_BlackMesa,           /**< Black Mesa Multiplayer */
	Engine_DOI                  /**< Day of Infamy */
};

enum FindMapResult
{
	// A direct match for this name was found
	FindMap_Found,
	// No match for this map name could be found.
	FindMap_NotFound,
	// A fuzzy match for this map name was found.
	// Ex: cp_dust -> cp_dustbowl, c1m1 -> c1m1_hotel
	// Only supported for maps that the engine knows about. (This excludes workshop maps on Orangebox).
	FindMap_FuzzyMatch,
	// A non-canonical match for this map name was found.
	// Ex: workshop/1234 -> workshop/cp_qualified_name.ugc1234
	// Only supported on "Orangebox" games with workshop support.
	FindMap_NonCanonical,
	// No currently available match for this map name could be found, but it may be possible to load
	// Only supported on "Orangebox" games with workshop support.
	FindMap_PossiblyAvailable
};

#define INVALID_ENT_REFERENCE 0xFFFFFFFF

enum ClientRangeType
{
	RangeType_Visibility = 0,
	RangeType_Audibility
};

static int NOALPHA_COLOR[4] = { 255, 255, 255, 0 };

// ENTITY_PROP_STOCKS.INC

using MoveType = MoveType_t;

enum RenderMode
{
	RENDER_NORMAL,              /**< src */
	RENDER_TRANSCOLOR,          /**< c*a+dest*(1-a) */
	RENDER_TRANSTEXTURE,        /**< src*a+dest*(1-a) */
	RENDER_GLOW,                /**< src*a+dest -- No Z buffer checks -- Fixed size in screen space */
	RENDER_TRANSALPHA,          /**< src*srca+dest*(1-srca) */
	RENDER_TRANSADD,            /**< src*a+dest */
	RENDER_ENVIRONMENTAL,       /**< not drawn, used for environmental effects */
	RENDER_TRANSADDFRAMEBLEND,  /**< use a fractional frame value to blend between animation frames */
	RENDER_TRANSALPHAADD,       /**< src + dest*(1-a) */
	RENDER_WORLDGLOW,           /**< Same as kRenderGlow but not fixed size in screen space */
	RENDER_NONE                 /**< Don't render. */
};

enum RenderFx
{
	RENDERFX_NONE = 0,
	RENDERFX_PULSE_SLOW,
	RENDERFX_PULSE_FAST,
	RENDERFX_PULSE_SLOW_WIDE,
	RENDERFX_PULSE_FAST_WIDE,
	RENDERFX_FADE_SLOW,
	RENDERFX_FADE_FAST,
	RENDERFX_SOLID_SLOW,
	RENDERFX_SOLID_FAST,
	RENDERFX_STROBE_SLOW,
	RENDERFX_STROBE_FAST,
	RENDERFX_STROBE_FASTER,
	RENDERFX_FLICKER_SLOW,
	RENDERFX_FLICKER_FAST,
	RENDERFX_NO_DISSIPATION,
	RENDERFX_DISTORT,           /**< Distort/scale/translate flicker */
	RENDERFX_HOLOGRAM,          /**< kRenderFxDistort + distance fade */
	RENDERFX_EXPLODE,           /**< Scale up really big! */
	RENDERFX_GLOWSHELL,         /**< Glowing Shell */
	RENDERFX_CLAMP_MIN_SCALE,   /**< Keep this sprite from getting very small (SPRITES only!) */
	RENDERFX_ENV_RAIN,          /**< for environmental rendermode, make rain */
	RENDERFX_ENV_SNOW,          /**<  "        "            "    , make snow */
	RENDERFX_SPOTLIGHT,         /**< TEST CODE for experimental spotlight */
	RENDERFX_RAGDOLL,           /**< HACKHACK: TEST CODE for signalling death of a ragdoll character */
	RENDERFX_PULSE_FAST_WIDER,
	RENDERFX_MAX
};

// These defines are for client button presses.
#define IN_ATTACK                (1 << 0)
#define IN_JUMP                  (1 << 1)
#define IN_DUCK                  (1 << 2)
#define IN_FORWARD               (1 << 3)
#define IN_BACK                  (1 << 4)
#define IN_USE                   (1 << 5)
#define IN_CANCEL                (1 << 6)
#define IN_LEFT                  (1 << 7)
#define IN_RIGHT                 (1 << 8)
#define IN_MOVELEFT              (1 << 9)
#define IN_MOVERIGHT             (1 << 10)
#define IN_ATTACK2               (1 << 11)
#define IN_RUN                   (1 << 12)
#define IN_RELOAD                (1 << 13)
#define IN_ALT1                  (1 << 14)
#define IN_ALT2                  (1 << 15)
#define IN_SCORE                 (1 << 16)   /**< Used by client.dll for when scoreboard is held down */
#define IN_SPEED                 (1 << 17)   /**< Player is holding the speed key */
#define IN_WALK                  (1 << 18)   /**< Player holding walk key */
#define IN_ZOOM                  (1 << 19)   /**< Zoom key for HUD zoom */
#define IN_WEAPON1               (1 << 20)   /**< weapon defines these bits */
#define IN_WEAPON2               (1 << 21)   /**< weapon defines these bits */
#define IN_BULLRUSH              (1 << 22)
#define IN_GRENADE1              (1 << 23)   /**< grenade 1 */
#define IN_GRENADE2              (1 << 24)   /**< grenade 2 */
#define IN_ATTACK3               (1 << 25)

// SDKTOOLS_GAMERULES.INC

enum RoundState
{
	// initialize the game, create teams
	RoundState_Init,

	//Before players have joined the game. Periodically checks to see if enough players are ready
	//to start a game. Also reverts to this when there are no active players
	RoundState_Pregame,

	//The game is about to start, wait a bit and spawn everyone
	RoundState_StartGame,

	//All players are respawned, frozen in place
	RoundState_Preround,

	//Round is on, playing normally
	RoundState_RoundRunning,

	//Someone has won the round
	RoundState_TeamWin,

	//Noone has won, manually restart the game, reset scores
	RoundState_Restart,

	//Noone has won, restart the game
	RoundState_Stalemate,

	//Game is over, showing the scoreboard etc
	RoundState_GameOver,

	//Game is over, doing bonus round stuff
	RoundState_Bonus,

	//Between rounds
	RoundState_BetweenRounds
};

// SDKTOOLS_TEMPENTS_STOCKS.INC

#define TE_EXPLFLAG_NONE            0x0   /**< all flags clear makes default Half-Life explosion */
#define TE_EXPLFLAG_NOADDITIVE      0x1   /**< sprite will be drawn opaque (ensure that the sprite you send is a non-additive sprite) */
#define TE_EXPLFLAG_NODLIGHTS       0x2   /**< do not render dynamic lights */
#define TE_EXPLFLAG_NOSOUND         0x4   /**< do not play client explosion sound */
#define TE_EXPLFLAG_NOPARTICLES     0x8   /**< do not draw particles */
#define TE_EXPLFLAG_DRAWALPHA       0x10  /**< sprite will be drawn alpha */
#define TE_EXPLFLAG_ROTATE          0x20  /**< rotate the sprite randomly */
#define TE_EXPLFLAG_NOFIREBALL      0x40  /**< do not draw a fireball */
#define TE_EXPLFLAG_NOFIREBALLSMOKE 0x80  /**< do not draw smoke with the fireball */

#define FBEAM_STARTENTITY   0x00000001
#define FBEAM_ENDENTITY     0x00000002
#define FBEAM_FADEIN        0x00000004
#define FBEAM_FADEOUT       0x00000008
#define FBEAM_SINENOISE     0x00000010
#define FBEAM_SOLID         0x00000020
#define FBEAM_SHADEIN       0x00000040
#define FBEAM_SHADEOUT      0x00000080
#define FBEAM_ONLYNOISEONCE 0x00000100  /**< Only calculate our noise once */
#define FBEAM_NOTILE        0x00000200
#define FBEAM_USE_HITBOXES  0x00000400  /**< Attachment indices represent hitbox indices instead when this is set. */
#define FBEAM_STARTVISIBLE  0x00000800  /**< Has this client actually seen this beam's start entity yet? */
#define FBEAM_ENDVISIBLE    0x00001000  /**< Has this client actually seen this beam's end entity yet? */
#define FBEAM_ISACTIVE      0x00002000
#define FBEAM_FOREVER       0x00004000
#define FBEAM_HALOBEAM      0x00008000  /**< When drawing a beam with a halo, don't ignore the segments and endwidth */

// CORE.INC

#define SOURCEMOD_PLUGINAPI_VERSION     5

/**
 * Specifies what to do after a hook completes.
 */
enum Action
{
	Plugin_Continue = 0,    /**< Continue with the original action */
	Plugin_Changed = 1,     /**< Inputs or outputs have been overridden with new values */
	Plugin_Handled = 3,     /**< Handle the action at the end (don't call it) */
	Plugin_Stop = 4         /**< Immediately stop the hook chain and handle the original */
};

/**
 * Specifies identity types.
 */
enum Identity
{
	Identity_Core = 0,
	Identity_Extension = 1,
	Identity_Plugin = 2
};

/**
 * Plugin information properties. Plugins can declare a global variable with
 * their info. Example,
 *
 *   public Plugin myinfo = {
 *   	name = "Admin Help",
 *   	author = "AlliedModders LLC",
 *   	description = "Display command information",
 *   	version = "1.0",
 *   	url = "http://www.sourcemod.net/"
 *   };
 *
 * SourceMod will display this information when a user inspects plugins in the
 * console.
 */
enum PluginInfo
{
	PlInfo_Name,            /**< Plugin name */
	PlInfo_Author,          /**< Plugin author */
	PlInfo_Description,     /**< Plugin description */
	PlInfo_Version,         /**< Plugin version */
	PlInfo_URL              /**< Plugin URL */
};

// SDKTOOLS_TRACE.INC

#define CONTENTS_CURRENT_0      0x40000
#define CONTENTS_CURRENT_90     0x80000
#define CONTENTS_CURRENT_180    0x100000
#define CONTENTS_CURRENT_270    0x200000
#define CONTENTS_CURRENT_UP     0x400000
#define CONTENTS_CURRENT_DOWN   0x800000

#define CONTENTS_ORIGIN         0x1000000   /**< removed before bsp-ing an entity. */
#define CONTENTS_MONSTER        0x2000000   /**< should never be on a brush, only in game. */
#define CONTENTS_DEBRIS         0x4000000
#define CONTENTS_DETAIL         0x8000000   /**< brushes to be added after vis leafs. */
#define CONTENTS_TRANSLUCENT    0x10000000  /**< auto set if any surface has trans. */
#define CONTENTS_LADDER         0x20000000
#define CONTENTS_HITBOX         0x40000000  /**< use accurate hitboxes on trace. */

#define SURF_LIGHT       0x0001      /**< value will hold the light strength */
#define SURF_SKY2D       0x0002      /**< don't draw, indicates we should skylight + draw 2d sky but not draw the 3D skybox */
#define SURF_SKY         0x0004      /**< don't draw, but add to skybox */
#define SURF_WARP        0x0008      /**< turbulent water warp */
#define SURF_TRANS       0x0010
#define SURF_NOPORTAL    0x0020      /**< the surface can not have a portal placed on it */
#define SURF_TRIGGER     0x0040      /**< This is an xbox hack to work around elimination of trigger surfaces, which breaks occluders */
#define SURF_NODRAW      0x0080      /**< don't bother referencing the texture */

#define SURF_HINT        0x0100      /**< make a primary bsp splitter */

#define SURF_SKIP        0x0200      /**< completely ignore, allowing non-closed brushes */
#define SURF_NOLIGHT     0x0400      /**< Don't calculate light */
#define SURF_BUMPLIGHT   0x0800      /**< calculate three lightmaps for the surface for bumpmapping */
#define SURF_NOSHADOWS   0x1000      /**< Don't receive shadows */
#define SURF_NODECALS    0x2000      /**< Don't receive decals */
#define SURF_NOCHOP      0x4000      /**< Don't subdivide patches on this surface */
#define SURF_HITBOX      0x8000      /**< surface is part of a hitbox */

#define PARTITION_SOLID_EDICTS        (1 << 1) /**< every edict_t that isn't SOLID_TRIGGER or SOLID_NOT (and static props) */
#define PARTITION_TRIGGER_EDICTS      (1 << 2) /**< every edict_t that IS SOLID_TRIGGER */
#define PARTITION_NON_STATIC_EDICTS   (1 << 5) /**< everything in solid & trigger except the static props, includes SOLID_NOTs */
#define PARTITION_STATIC_PROPS        (1 << 7)

#define DISPSURF_FLAG_SURFACE         (1<<0)
#define DISPSURF_FLAG_WALKABLE        (1<<1)
#define DISPSURF_FLAG_BUILDABLE       (1<<2)
#define DISPSURF_FLAG_SURFPROP1       (1<<3)
#define DISPSURF_FLAG_SURFPROP2       (1<<4)

enum RayType
{
	RayType_EndPoint,   /**< The trace ray will go from the start position to the end position. */
	RayType_Infinite    /**< The trace ray will go from the start position to infinity using a direction vector. */
};

// SDKTOOLS_ENGINE.INC

#define MAX_LIGHTSTYLES 64

// SDKTOOLS_VOICE.INC

#define VOICE_NORMAL        0   /**< Allow the client to listen and speak normally. */
#define VOICE_MUTED         1   /**< Mutes the client from speaking to everyone. */
#define VOICE_SPEAKALL      2   /**< Allow the client to speak to everyone. */
#define VOICE_LISTENALL     4   /**< Allow the client to listen to everyone. */
#define VOICE_TEAM          8   /**< Allow the client to always speak to team, even when dead. */
#define VOICE_LISTENTEAM    16  /**< Allow the client to always hear teammates, including dead ones. */

enum ListenOverride
{
	Listen_Default = 0, /**< Leave it up to the game */
	Listen_No,          /**< Can't hear */
	Listen_Yes          /**< Can hear */
};

// LANG.INC

#define LANG_SERVER 0      /**< Translate using the server's language */

// ADT_ARRAY.INC
using ArrayListHandle = int;

// COMMANDFILTERS.INC

#define MAX_TARGET_LENGTH           64

#define COMMAND_FILTER_ALIVE        (1<<0)      /**< Only allow alive players */
#define COMMAND_FILTER_DEAD         (1<<1)      /**< Only filter dead players */
#define COMMAND_FILTER_CONNECTED    (1<<2)      /**< Allow players not fully in-game */
#define COMMAND_FILTER_NO_IMMUNITY  (1<<3)      /**< Ignore immunity rules */
#define COMMAND_FILTER_NO_MULTI     (1<<4)      /**< Do not allow multiple target patterns */
#define COMMAND_FILTER_NO_BOTS      (1<<5)      /**< Do not allow bots to be targetted */

#define COMMAND_TARGET_NONE          0          /**< No target was found */
#define COMMAND_TARGET_NOT_ALIVE    -1          /**< Single client is not alive */
#define COMMAND_TARGET_NOT_DEAD     -2          /**< Single client is not dead */
#define COMMAND_TARGET_NOT_IN_GAME  -3          /**< Single client is not in game */
#define COMMAND_TARGET_IMMUNE       -4          /**< Single client is immune */
#define COMMAND_TARGET_EMPTY_FILTER -5          /**< A multi-filter (such as @all) had no targets */
#define COMMAND_TARGET_NOT_HUMAN    -6          /**< Target was not human */
#define COMMAND_TARGET_AMBIGUOUS    -7          /**< Partial name had too many targets */

// SDKTOOLS_SOUND.INC

/**
 * Sound should be from the target client.
 */
#define SOUND_FROM_PLAYER       -2

 /**
  * Sound should be from the listen server player.
  */
#define SOUND_FROM_LOCAL_PLAYER -1

  /**
   * Sound is from the world.
   */
#define SOUND_FROM_WORLD        0

   /**
	* Sound channels.
	*/
enum
{
	SNDCHAN_REPLACE = -1,       /**< Unknown */
	SNDCHAN_AUTO = 0,           /**< Auto */
	SNDCHAN_WEAPON = 1,         /**< Weapons */
	SNDCHAN_VOICE = 2,          /**< Voices */
	SNDCHAN_ITEM = 3,           /**< Items */
	SNDCHAN_BODY = 4,           /**< Player? */
	SNDCHAN_STREAM = 5,         /**< "Stream channel from the static or dynamic area" */
	SNDCHAN_STATIC = 6,         /**< "Stream channel from the static area" */
	SNDCHAN_VOICE_BASE = 7,     /**< "Channel for network voice data" */
	SNDCHAN_USER_BASE = 135     /**< Anything >= this is allocated to game code */
};

/**
 * Various predefined sound levels in dB.
 */
enum
{
	SNDLEVEL_NONE = 0,          /**< None */
	SNDLEVEL_RUSTLE = 20,       /**< Rustling leaves */
	SNDLEVEL_WHISPER = 25,      /**< Whispering */
	SNDLEVEL_LIBRARY = 30,      /**< In a library */
	SNDLEVEL_FRIDGE = 45,       /**< Refrigerator */
	SNDLEVEL_HOME = 50,         /**< Average home (3.9 attn) */
	SNDLEVEL_CONVO = 60,        /**< Normal conversation (2.0 attn) */
	SNDLEVEL_DRYER = 60,        /**< Clothes dryer */
	SNDLEVEL_DISHWASHER = 65,   /**< Dishwasher/washing machine (1.5 attn) */
	SNDLEVEL_CAR = 70,          /**< Car or vacuum cleaner (1.0 attn) */
	SNDLEVEL_NORMAL = 75,       /**< Normal sound level */
	SNDLEVEL_TRAFFIC = 75,      /**< Busy traffic (0.8 attn) */
	SNDLEVEL_MINIBIKE = 80,     /**< Mini-bike, alarm clock (0.7 attn) */
	SNDLEVEL_SCREAMING = 90,    /**< Screaming child (0.5 attn) */
	SNDLEVEL_TRAIN = 100,       /**< Subway train, pneumatic drill (0.4 attn) */
	SNDLEVEL_HELICOPTER = 105,  /**< Helicopter */
	SNDLEVEL_SNOWMOBILE = 110,  /**< Snow mobile */
	SNDLEVEL_AIRCRAFT = 120,    /**< Auto horn, aircraft */
	SNDLEVEL_RAIDSIREN = 130,   /**< Air raid siren */
	SNDLEVEL_GUNFIRE = 140,     /**< Gunshot, jet engine (0.27 attn) */
	SNDLEVEL_ROCKET = 180       /**< Rocket launching (0.2 attn) */
};

#define SNDVOL_NORMAL       1.0     /**< Normal volume */
#define SNDPITCH_NORMAL     100     /**< Normal pitch */
#define SNDPITCH_LOW        95      /**< A low pitch */
#define SNDPITCH_HIGH       120     /**< A high pitch */
#define SNDATTN_NONE        0.0     /**< No attenuation */
#define SNDATTN_NORMAL      0.8     /**< Normal attenuation */
#define SNDATTN_STATIC      1.25    /**< Static attenuation? */
#define SNDATTN_RICOCHET    1.5     /**< Ricochet effect */
#define SNDATTN_IDLE        2.0     /**< Idle attenuation? */

// SDKTOOLS.INC

enum SDKCallType
{
	SDKCall_Static,         /**< Static call */
	SDKCall_Entity,         /**< CBaseEntity call */
	SDKCall_Player,         /**< CBasePlayer call */
	SDKCall_GameRules,      /**< CGameRules call */
	SDKCall_EntityList,     /**< CGlobalEntityList call */
	SDKCall_Raw             /**< |this| pointer with an arbitrary address */
};

enum SDKLibrary
{
	SDKLibrary_Server,      /**< server.dll/server_i486.so */
	SDKLibrary_Engine       /**< engine.dll/engine_*.so */
};

enum SDKFuncConfSource
{
	SDKConf_Virtual = 0,    /**< Read a virtual index from the Offsets section */
	SDKConf_Signature = 1,  /**< Read a signature from the Signatures section */
	SDKConf_Address = 2     /**< Read an address from the Addresses section */
};

enum SDKType
{
	SDKType_CBaseEntity,    /**< CBaseEntity (always as pointer) */
	SDKType_CBasePlayer,    /**< CBasePlayer (always as pointer) */
	SDKType_Vector,         /**< Vector (pointer, byval, or byref) */
	SDKType_QAngle,         /**< QAngles (pointer, byval, or byref) */
	SDKType_PlainOldData,   /**< Integer/generic data <=32bit (any) */
	SDKType_Float,          /**< Float (any) */
	SDKType_Edict,          /**< edict_t (always as pointer) */
	SDKType_String,         /**< NULL-terminated string (always as pointer) */
	SDKType_Bool            /**< Boolean (any) */
};

enum SDKPassMethod
{
	SDKPass_Pointer,        /**< Pass as a pointer */
	SDKPass_Plain,          /**< Pass as plain data */
	SDKPass_ByValue,        /**< Pass an object by value */
	SDKPass_ByRef           /**< Pass an object by reference */
};

#define VDECODE_FLAG_ALLOWNULL      (1<<0)    /**< Allow NULL for pointers */
#define VDECODE_FLAG_ALLOWNOTINGAME (1<<1)    /**< Allow players not in game */
#define VDECODE_FLAG_ALLOWWORLD     (1<<2)    /**< Allow World entity */
#define VDECODE_FLAG_BYREF          (1<<3)    /**< Floats/ints by reference */

#define VENCODE_FLAG_COPYBACK       (1<<0)    /**< Copy back data once done */

// SOURCEMOD.INC

enum APLRes
{
	APLRes_Success = 0,     /**< Plugin should load */
	APLRes_Failure,         /**< Plugin shouldn't load and should display an error */
	APLRes_SilentFailure    /**< Plugin shouldn't load but do so silently */
};

#define MAPLIST_FLAG_MAPSFOLDER    (1<<0)    /**< On failure, use all maps in the maps folder. */
#define MAPLIST_FLAG_CLEARARRAY    (1<<1)    /**< If an input array is specified, clear it before adding. */
#define MAPLIST_FLAG_NO_DEFAULT    (1<<2)    /**< Do not read "default" or "mapcyclefile" on failure. */

/**
 * Represents how many bytes we can read from an address with one load
 */
enum NumberType
{
	NumberType_Int8,
	NumberType_Int16,
	NumberType_Int32
};

using Address = int;
using GameDataHandle = int;

#define Address_Null = 0               // a typical invalid result when an address lookup fails

static int MINUS_ONE = -1;

static int IVEC_2[2] = { 0, 0 };
