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

#define LANG_SERVER 0

static constexpr float NULL_VECTOR[] = { 0.0f, 0.0f, 0.0f };

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

enum ImmunityType
{
	Immunity_Default = 1,   // Deprecated.
	Immunity_Global         // Deprecated.
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

enum Action
{
	Plugin_Continue = 0, /**< Continue with the original action */
	Plugin_Changed = 1, /**< Inputs or outputs have been overridden with new values */
	Plugin_Handled = 3, /**< Handle the action at the end (don't call it) */
	Plugin_Stop = 4, /**< Immediately stop the hook chain and handle the original */
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

/**
 * @section For more information on these, see the HL2SDK (public/edict.h)
 */
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
