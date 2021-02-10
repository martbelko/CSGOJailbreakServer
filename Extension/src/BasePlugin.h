#pragma once

#include "PublicManager.h"

class BasePlugin
{
public:
	// SOURCEMOD.INC

	/**
	 * Called when the plugin is fully initialized and all known external references
	 * are resolved. This is only called once in the lifetime of the plugin, and is
	 * paired with OnPluginEnd().
	 *
	 * If any run-time error is thrown during this callback, the plugin will be marked
	 * as failed.
	 */
	virtual void OnPluginStart()
	{
	}

	/**
	 * Called when the plugin is about to be unloaded.
	 *
	 * It is not necessary to close any handles or remove hooks in this function.
	 * SourceMod guarantees that plugin shutdown automatically and correctly releases
	 * all resources.
	 */
	virtual void OnPluginEnd()
	{
	}

	/**
	 * Called when the plugin's pause status is changing.
	 *
	 * @param pause         True if the plugin is being paused, false otherwise.
	 */
	virtual void OnPluginPauseChange(bool pause)
	{
	}

	/**
	 * Called before every server frame.  Note that you should avoid
	 * doing expensive computations or declaring large local arrays.
	 */
	virtual void OnGameFrame()
	{
	}

	/**
	 * Called when the map is loaded.
	 *
	 * @note This used to be OnServerLoad(), which is now deprecated.
	 *       Plugins still using the old forward will work.
	 */
	virtual void OnMapStart()
	{
	}

	/**
	 * Called right before a map ends.
	 */
	virtual void OnMapEnd()
	{
	}

	/**
	 * Called when the map has loaded, servercfgfile (server.cfg) has been
	 * executed, and all plugin configs are done executing.  This is the best
	 * place to initialize plugin functions which are based on cvar data.
	 *
	 * @note This will always be called once and only once per map.  It will be
	 *       called after OnMapStart().
	 */
	virtual void OnConfigsExecuted()
	{
	}

	/**
	 * This is called once, right after OnMapStart() but any time before
	 * OnConfigsExecuted().  It is called after the "exec sourcemod.cfg"
	 * command and all AutoExecConfig() exec commands have been added to
	 * the ServerCommand() buffer.
	 *
	 * If you need to load per-map settings that override default values,
	 * adding commands to the ServerCommand() buffer here will guarantee
	 * that they're set before OnConfigsExecuted().
	 *
	 * Unlike OnMapStart() and OnConfigsExecuted(), this is not called on
	 * late loads that occur after OnMapStart().
	 */
	virtual void OnAutoConfigsBuffered()
	{
	}

	/**
	 * Called after all plugins have been loaded.  This is called once for
	 * every plugin.  If a plugin late loads, it will be called immediately
	 * after OnPluginStart().
	 */
	virtual void OnAllPluginsLoaded()
	{
	}

	/**
	 * Returns whether a library exists.  This function should be considered
	 * expensive; it should only be called on plugin to determine availability
	 * of resources.  Use OnLibraryAdded()/OnLibraryRemoved() to detect changes
	 * in libraries.
	 *
	 * @param name          Library name of a plugin or extension.
	 * @return              True if exists, false otherwise.
	 */
	virtual void OnLibraryAdded(const char* name)
	{
	}

	/**
	 * Called right before a library is removed.
	 * A library is either a plugin name or extension name, as
	 * exposed via its include file.
	 *
	 * @param name          Library name.
	 */
	virtual void OnLibraryRemoved(const char* name)
	{
	}

	/**
	 * Called when a client has sent chat text.  This must return either true or
	 * false to indicate that a client is or is not spamming the server.
	 *
	 * The return value is a hint only.  Core or another plugin may decide
	 * otherwise.
	 *
	 * @param client        Client index.  The server (0) will never be passed.
	 * @return              True if client is spamming the server, false otherwise.
	 */
	virtual bool OnClientFloodCheck(int client)
	{
		return false;
	}

	/**
	 * Called after a client's flood check has been computed.  This can be used
	 * by antiflood algorithms to decay/increase flooding weights.
	 *
	 * Since the result from "OnClientFloodCheck" isn't guaranteed to be the
	 * final result, it is generally a good idea to use this to play with other
	 * algorithms nicely.
	 *
	 * @param client        Client index.  The server (0) will never be passed.
	 * @param blocked       True if client flooded last "say", false otherwise.
	 */
	virtual void OnClientFloodResult(int client, bool blocked)
	{
	}

	// SDKTOOLS_VOICE.INC

	/**
	 * Called when a client is speaking.
	 *
	 * @param client        The client index
	 */
	virtual void OnClientSpeaking(int client)
	{
	}

	/**
	 * Called once a client speaking end.
	 *
	 * @param client        The client index
	 */
	virtual void OnClientSpeakingEnd(int client)
	{
	}

	// LOGGING.INC

	/**
	 * Called when an action is going to be logged.
	 *
	 * @param source        Handle to the object logging the action, or INVALID_HANDLE
	 *                      if Core is logging the action.
	 * @param ident         Type of object logging the action (plugin, ext, or core).
	 * @param client        Client the action is from; 0 for server, -1 if not applicable.
	 * @param target        Client the action is targetting, or -1 if not applicable.
	 * @param message       Message that is being logged.
	 * @return              Plugin_Continue will perform the default logging behavior.
	 *                      Plugin_Handled will stop Core from logging the message.
	 *                      Plugin_Stop is the same as Handled, but prevents any other
	 *                      plugins from handling the message.
	 */
	virtual Action OnLogAction(Handle source, Identity ident, int client, int target, const char* message)
	{
		return Plugin_Continue;
	}

	// TIMERS.INC

	/**
	 * Notification that the map's time left has changed via a change in the time
	 * limit or a change in the game rules (such as mp_restartgame).  This is useful
	 * for plugins trying to create timers based on the time left in the map.
	 *
	 * Calling ExtendMapTimeLimit() from here, without proper precaution, will
	 * cause infinite recursion.
	 *
	 * If the operation is not supported, this will never be called.

	 * If the server has not yet processed any frames (i.e. no players have joined
	 * the map yet), then this will be called once the server begins ticking, even
	 * if there is no time limit set.
	 */
	virtual void OnMapTimeLeftChanged()
	{
	}

	// SDKTOOLS_HOOKS.INC

	/**
	 * @brief Called when a clients movement buttons are being processed
	 *
	 * @param client        Index of the client.
	 * @param buttons       Copyback buffer containing the current commands (as bitflags - see entity_prop_stocks.inc).
	 * @param impulse       Copyback buffer containing the current impulse command.
	 * @param vel           Players desired velocity.
	 * @param angles        Players desired view angles.
	 * @param weapon        Entity index of the new weapon if player switches weapon, 0 otherwise.
	 * @param subtype       Weapon subtype when selected from a menu.
	 * @param cmdnum        Command number. Increments from the first command sent.
	 * @param tickcount     Tick count. A client's prediction based on the server's GetGameTickCount value.
	 * @param seed          Random seed. Used to determine weapon recoil, spread, and other predicted elements.
	 * @param mouse         Mouse direction (x, y).
	 * @return              Plugin_Handled to block the commands from being processed, Plugin_Continue otherwise.
	 *
	 * @note To see if all 11 params are available, use FeatureType_Capability and FEATURECAP_PLAYERRUNCMD_11PARAMS.
	 */
	virtual Action OnPlayerRunCmd(int client, int& buttons, int& impulse, float vel[3], float angles[3], int& weapon, int& subtype, int& cmdnum, int& tickcount, int& seed, int mouse[2])
	{
		return Plugin_Continue;
	}

	/**
	 * Called after a clients movement buttons were processed.
	 *
	 * @param client        Index of the client.
	 * @param buttons       The current commands (as bitflags - see entity_prop_stocks.inc).
	 * @param impulse       The current impulse command.
	 * @param vel           Players desired velocity.
	 * @param angles        Players desired view angles.
	 * @param weapon        Entity index of the new weapon if player switches weapon, 0 otherwise.
	 * @param subtype       Weapon subtype when selected from a menu.
	 * @param cmdnum        Command number. Increments from the first command sent.
	 * @param tickcount     Tick count. A client's prediction based on the server's GetGameTickCount value.
	 * @param seed          Random seed. Used to determine weapon recoil, spread, and other predicted elements.
	 * @param mouse         Mouse direction (x, y).
	 */
	virtual void OnPlayerRunCmdPost(int client, int buttons, int impulse, const float vel[3], const float angles[3], int weapon, int subtype, int cmdnum, int tickcount, int seed, const int mouse[2])
	{
	}

	// SDKHOOKS.INC

	/**
	 * When an entity is created
	 *
	 * @param entity        Entity index
	 * @param classname     Class name
	 */
	virtual void OnEntityCreated(int entity, const char* className)
	{
	}

	/**
	 * When an entity is spawned
	 *
	 * @param entity        Entity index
	 * @param classname     Class name
	 *
	 * @note Check for support at runtime using GetFeatureStatus on SDKHook_OnEntitySpawned capability.
	 */
	virtual void OnEntitySpawned(int entity, const char* className)
	{
	}

	/**
	 * When an entity is destroyed
	 *
	 * @param entity        Entity index or edict reference.
	 */
	virtual void OnEntityDestroyed(int entity)
	{
	}

	/**
	 * When the game description is retrieved
	 *
	 * @note Not supported on ep2v.
	 *
	 * @param gameDesc      Game description
	 * @return              Plugin_Changed if gameDesc has been edited, else no change.
	 */
	virtual Action OnGetGameDescription(char gameDesc[64])
	{
		return Plugin_Continue;
	}

	/**
	 * When the level is initialized
	 *
	 * @param mapName       Name of the map
	 * @param mapEntities   Entities of the map
	 * @return              Plugin_Changed if mapEntities has been edited, else no change.
	 */
	virtual Action OnLevelInit(const char* mapName, char mapEntities[2097152])
	{
		return Plugin_Continue;
	}

	// CSTRIKE.INC

	/**
	 * Called when a player attempts to purchase an item.
	 * Return Plugin_Continue to allow the purchase or return a
	 * higher action to deny.
	 *
	 * @param client        Client index
	 * @param weapon        User input for weapon name
	 */
	virtual Action CS_OnBuyCommand(int client, const char* weapon)
	{
		return Plugin_Continue;
	}

	/**
	 * Called when CSWeaponDrop is called
	 * Return Plugin_Continue to allow the call or return a
	 * higher action to block.
	 *
	 * @param client        Client index
	 * @param weaponIndex   Weapon index
	 */
	virtual Action CS_OnCSWeaponDrop(int client, int weaponIndex)
	{
		return Plugin_Continue;
	}

	/**
	 * Called when game retrieves a weapon's price for a player.
	 * Return Plugin_Continue to use default value or return a higher
	 * action to use a newly-set price.
	 *
	 * @note This can be called multiple times per weapon purchase
	 *
	 * @param client        Client index
	 * @param weapon        Weapon classname
	 * @param price         Buffer param for the price of the weapon
	 *
	 * @note Not all "weapons" call GetWeaponPrice. Example: c4, knife, vest, vest helmet, night vision.
	 */
	virtual Action CS_OnGetWeaponPrice(int client, const char* weapon, int& price)
	{
		return Plugin_Continue;
	}

	/**
	 * Called when TerminateRound is called.
	 * Return Plugin_Continue to ignore, return Plugin_Changed to continue,
	 * using the given delay and reason, or return Plugin_Handled or a higher
	 * action to block TerminateRound from firing.
	 *
	 * @param delay         Time (in seconds) until new round starts
	 * @param reason        Reason for round end
	 */
	virtual Action CS_OnTerminateRound(float& delay, CSRoundEndReason& reason)
	{
		return Plugin_Continue;
	}

	// CONSOLE.INC

	/**
	 * Global listener for the chat commands.
	 *
	 * @param client        Client index.
	 * @param command       Command name.
	 * @param sArgs         Chat argument string.
	 *
	 * @return              An Action value. Returning Plugin_Handled bypasses the game function call.
	 *                      Returning Plugin_Stop bypasses the post hook as well as the game function.
	 */
	virtual Action OnClientSayCommand(int client, const char* command, const char* args)
	{
		return Plugin_Continue;
	}

	/**
	 * Global post listener for the chat commands.
	 *
	 * @param client        Client index.
	 * @param command       Command name.
	 * @param sArgs         Chat argument string.
	 */
	virtual void OnClientSayCommandPost(int client, const char* command, const char* args)
	{
	}

	// CLIENTS.INC

	/**
	 * Called on client connection.  If you return true, the client will be allowed in the server.
	 * If you return false (or return nothing), the client will be rejected.  If the client is
	 * rejected by this forward or any other, OnClientDisconnect will not be called.
	 *
	 * Note: Do not write to rejectmsg if you plan on returning true.  If multiple plugins write
	 * to the string buffer, it is not defined which plugin's string will be shown to the client,
	 * but it is guaranteed one of them will.
	 *
	 * @param client        Client index.
	 * @param rejectMsg     Buffer to store the rejection message when the connection is refused.
	 * @param maxlen        Maximum number of characters for rejection buffer.
	 * @return              True to validate client's connection, false to refuse it.
	 */
	virtual bool OnClientConnect(int client, char* rejectMsg, int maxlen)
	{
		return true;
	}

	/**
	 * Called once a client successfully connects.  This callback is paired with OnClientDisconnect.
	 *
	 * @param client        Client index.
	 */
	virtual void OnClientConnected(int client)
	{
	}

	/**
	 * Called when a client is entering the game.
	 *
	 * Whether a client has a steamid is undefined until OnClientAuthorized
	 * is called, which may occur either before or after OnClientPutInServer.
	 * Similarly, use OnClientPostAdminCheck() if you need to verify whether
	 * connecting players are admins.
	 *
	 * GetClientCount() will include clients as they are passed through this
	 * function, as clients are already in game at this point.
	 *
	 * @param client        Client index.
	 */
	virtual void OnClientPutInServer(int client)
	{
	}

	/**
	 * Called when a client is disconnecting from the server.
	 *
	 * @param client        Client index.
	 */
	virtual void OnClientDisconnect(int client)
	{
	}

	/**
	 * Called when a client is disconnected from the server.
	 *
	 * @param client        Client index.
	 */
	virtual void OnClientDisconnectPost(int client)
	{
	}

	/**
	 * Called when a client is sending a command.
	 *
	 * As of SourceMod 1.3, the client is guaranteed to be in-game.
	 * Use command listeners (console.inc) for more advanced hooks.
	 *
	 * @param client        Client index.
	 * @param argc          Number of arguments.
	 * @return              Plugin_Handled blocks the command from being sent,
	 *                      and Plugin_Continue resumes normal functionality.
	 */
	virtual Action OnClientCommand(int client, int argc)
	{
		return Plugin_Continue;
	}

	/**
	 * Called when a client is sending a KeyValues command.
	 *
	 * @param client        Client index.
	 * @param kv            Editable KeyValues data to be sent as the command.
	 *                      (This handle should not be stored and will be closed
	 *                      after this forward completes.)
	 * @return              Plugin_Handled blocks the command from being sent,
	 *                      and Plugin_Continue resumes normal functionality.
	 */
	virtual Action OnClientCommandKeyValues(int client, KeyValuesHandle kv)
	{
		return Plugin_Continue;
	}

	/**
	 * Called after a client has sent a KeyValues command.
	 *
	 * @param client        Client index.
	 * @param kv            KeyValues data sent as the command.
	 *                      (This handle should not be stored and will be closed
	 *                      after this forward completes.)
	 */
	virtual void OnClientCommandKeyValuesPost(int client, KeyValuesHandle kv)
	{
	}

	/**
	 * Called whenever the client's settings are changed.
	 *
	 * @param client        Client index.
	 */
	virtual void OnClientSettingsChanged(int client)
	{
	}

	/**
	 * Called when a client receives an auth ID.  The state of a client's
	 * authorization as an admin is not guaranteed here.  Use
	 * OnClientPostAdminCheck() if you need a client's admin status.
	 *
	 * This is called by bots, but the ID will be "BOT".
	 *
	 * @param client        Client index.
	 * @param auth          Client Steam2 id, if available, else engine auth id.
	 */
	virtual void OnClientAuthorized(int client, const char* auth)
	{
	}

	/**
	 * Called once a client is authorized and fully in-game, but
	 * before admin checks are done.  This can be used to override
	 * the default admin checks for a client.  You should only use
	 * this for overriding; use OnClientPostAdminCheck() instead
	 * if you want notification.
	 *
	 * Note: If handled/blocked, PostAdminCheck must be signalled
	 * manually via NotifyPostAdminCheck().
	 *
	 * This callback is guaranteed to occur on all clients, and always
	 * after each OnClientPutInServer() call.
	 *
	 * @param client        Client index.
	 * @return              Plugin_Handled to block admin checks.
	 */
	virtual Action OnClientPreAdminCheck(int client)
	{
		return Plugin_Continue;
	}

	/**
	 * Called directly before OnClientPostAdminCheck() as a method to
	 * alter administrative permissions before plugins perform final
	 * post-connect operations.
	 *
	 * In general, do not use this function unless you are specifically
	 * attempting to change access permissions.  Use OnClientPostAdminCheck()
	 * instead if you simply want to perform post-connect authorization
	 * routines.
	 *
	 * See OnClientPostAdminCheck() for more information.
	 *
	 * @param client        Client index.
	 */
	virtual void OnClientPostAdminFilter(int client)
	{
	}

	/**
	 * Called once a client is authorized and fully in-game, and
	 * after all post-connection authorizations have been performed.
	 *
	 * This callback is guaranteed to occur on all clients, and always
	 * after each OnClientPutInServer() call.
	 *
	 * @param client        Client index.
	 */
	virtual void OnClientPostAdminCheck(int client)
	{
	}
};
