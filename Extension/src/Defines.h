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
