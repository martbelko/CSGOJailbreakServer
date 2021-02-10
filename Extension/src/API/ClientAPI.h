public:
	/**
	 * @brief Returns the maximum number of human players allowed on the server.  This is
	 * a game-specific function used on newer games to limit the number of humans
	 * that can join a game and can be lower than MaxClients. It is the number often
	 * reflected in the server browser or when viewing the output of the status command.
	 * On unsupported games or modes without overrides, it will return the same value
	 * as MaxClients.
	 *
	 * You should not globally cache the value to GetMaxHumanPlayers() because it can change across
	 * game modes. You may still cache it locally.
	 *
	 * @return              Maximum number of humans allowed.
	 */
	static int GetMaxHumanPlayers()
	{
		return ExecFunc(s_GetMaxHumanPlayersFunc);
	}

	/**
	 * @brief Returns the client count put in the server.
	 *
	 * @param inGameOnly    If false connecting players are also counted.
	 * @return              Client count in the server.
	 */
	static int GetClientCount(bool inGameOnly = false)
	{
		return ExecFunc(s_GetClientCountFunc, inGameOnly);
	}

	/**
	 * @brief Returns the client's name.
	 *
	 * @param client        Player index.
	 * @param name          Buffer to store the client's name.
	 * @param maxlen        Maximum length of string buffer (includes NULL terminator).
	 * @return              True on success, false otherwise.
	 * @error               If the client is not connected an error will be thrown.
	 */
	static bool GetClientName(int client, char* name, int maxlen)
	{
		PushArg(s_GetClientNameFunc, client);
		PushArg(s_GetClientNameFunc, name, maxlen);
		PushArg(s_GetClientNameFunc, maxlen);
		return ExecFunc(s_GetClientNameFunc);
	}

	/**
	 * @brief Retrieves a client's IP address.
	 *
	 * @param client        Player index.
	 * @param ip            Buffer to store the client's ip address.
	 * @param maxlen        Maximum length of string buffer (includes NULL terminator).
	 * @param remport       Remove client's port from the ip string (true by default).
	 * @return              True on success, false otherwise.
	 * @error               If the client is not connected or the index is invalid.
	 */
	static bool GetClientIP(int client, char* ip, int maxlen, bool remport = true)
	{
		PushArg(s_GetClientIPFunc, client);
		PushArg(s_GetClientIPFunc, ip, maxlen);
		PushArg(s_GetClientIPFunc, maxlen);
		PushArg(s_GetClientIPFunc, remport);
		return ExecFunc(s_GetClientIPFunc);
	}

	/**
	 * @brief Retrieves a client's authentication string (SteamID).
	 *
	 * @param client        Player index.
	 * @param authType      Auth id type and format to use.
	 * @param auth          Buffer to store the client's auth id.
	 * @param maxlen        Maximum length of string buffer (includes NULL terminator).
	 * @param validate      Check backend validation status.
	 *                      DO NOT PASS FALSE UNLESS YOU UNDERSTAND THE CONSEQUENCES,
	 *                      You WILL KNOW if you need to use this, MOST WILL NOT.
	 * @return              True on success, false otherwise.
	 * @error               If the client is not connected or the index is invalid.
	 */
	static bool GetClientAuthId(int client, AuthIdType authType, char* auth, int maxlen, bool validate = true)
	{
		PushArg(s_GetClientAuthIdFunc, client);
		PushArg(s_GetClientAuthIdFunc, authType);
		PushArg(s_GetClientAuthIdFunc, auth, maxlen);
		PushArg(s_GetClientAuthIdFunc, maxlen);
		PushArg(s_GetClientAuthIdFunc, validate);
		return ExecFunc(s_GetClientAuthIdFunc);
	}

	/**
	 * @brief Returns the client's Steam account ID, a number uniquely identifying a given Steam account.
	 * This number is the basis for the various display SteamID forms, see the AuthIdType enum for examples.
	 *
	 * @param client        Client Index.
	 * @param validate      Check backend validation status.
	 *                      DO NOT PASS FALSE UNLESS YOU UNDERSTAND THE CONSEQUENCES,
	 *                      You WILL KNOW if you need to use this, MOST WILL NOT.
	 * @return              Steam account ID or 0 if not available.
	 * @error               If the client is not connected or the index is invalid.
	 */
	static int GetSteamAccountID(int client, bool validate = true)
	{
		return ExecFunc(s_GetSteamAccountIDFunc, client, validate);
	}

	/**
	 * @brief Retrieves a client's user id, which is an index incremented for every client
	 * that joins the server.
	 *
	 * @param client        Player index.
	 * @return              User id of the client.
	 * @error               If the client is not connected or the index is invalid.
	 */
	static int GetClientUserId(int client)
	{
		return ExecFunc(s_GetClientUserIdFunc, client);
	}

	/**
	 * @brief Returns if a certain player is connected.
	 *
	 * @param client        Player index.
	 * @return              True if player is connected to the server, false otherwise.
	 */
	static bool IsClientConnected(int client)
	{
		return ExecFunc(s_IsClientConnectedFunc, client);
	}

	/**
	 * @brief Returns if a certain player has entered the game.
	 *
	 * @param client        Player index (index does not have to be connected).
	 * @return              True if player has entered the game, false otherwise.
	 * @error               Invalid client index.
	 */
	static bool IsClientInGame(int client)
	{
		return ExecFunc(s_IsClientInGameFunc, client);
	}

	/**
	 * @brief Returns if a client is in the "kick queue" (i.e. the client will be kicked
	 * shortly and thus they should not appear as valid).
	 *
	 * @param client        Player index (must be connected).
	 * @return              True if in the kick queue, false otherwise.
	 * @error               Invalid client index.
	 */
	static bool IsClientInKickQueue(int client)
	{
		return ExecFunc(s_IsClientInKickQueueFunc, client);
	}

	/**
	 * @brief Returns if a certain player has been authenticated.
	 *
	 * @param client        Player index.
	 * @return              True if player has been authenticated, false otherwise.
	 */
	static bool IsClientAuthorized(int client)
	{
		return ExecFunc(s_IsClientAuthorizedFunc, client);
	}

	/**
	 * @brief Returns if a certain player is a fake client.
	 *
	 * @param client        Player index.
	 * @return              True if player is a fake client, false otherwise.
	 */
	static bool IsFakeClient(int client)
	{
		return ExecFunc(s_IsFakeClientFunc, client);
	}

	/**
	 * @brief Returns if a certain player is the SourceTV bot.
	 *
	 * @param client        Player index.
	 * @return              True if player is the SourceTV bot, false otherwise.
	 */
	static bool IsClientSourceTV(int client)
	{
		return ExecFunc(s_IsClientSourceTVFunc, client);
	}

	/**
	 * @brief Returns if a certain player is the Replay bot.
	 *
	 * @param client        Player index.
	 * @return              True if player is the Replay bot, false otherwise.
	 */
	static bool IsClientReplay(int client)
	{
		return ExecFunc(s_IsClientReplayFunc, client);
	}

	/**
	 * @brief Returns if a certain player is an observer/spectator.
	 *
	 * @param client        Player index.
	 * @return              True if player is an observer, false otherwise.
	 */
	static bool IsClientObserver(int client)
	{
		return ExecFunc(s_IsClientObserverFunc, client);
	}

	/**
	 * @brief Returns if the client is alive or dead.
	 *
	 * Note: This function was originally in SDKTools and was moved to core.
	 *
	 * @param client        Player's index.
	 * @return              True if the client is alive, false otherwise.
	 * @error               Invalid client index, client not in game, or no mod support.
	 */
	static bool IsPlayerAlive(int client)
	{
		return ExecFunc(s_IsPlayerAliveFunc, client);
	}

	/**
	 * @brief Retrieves values from client replicated keys.
	 *
	 * @param client        Player's index.
	 * @param key           Key string.
	 * @param value         Buffer to store value.
	 * @param maxlen        Maximum length of valve (UTF-8 safe).
	 * @return              True on success, false otherwise.
	 * @error               Invalid client index, or client not connected.
	 */
	static bool GetClientInfo(int client, const char* key, char* value, int maxlen)
	{
		PushArg(s_GetClientInfoFunc, client);
		PushArg(s_GetClientInfoFunc, key);
		PushArg(s_GetClientInfoFunc, value, maxlen);
		PushArg(s_GetClientInfoFunc, maxlen);
		return ExecFunc(s_GetClientInfoFunc);
	}

	/**
	 * @brief Retrieves a client's team index.
	 *
	 * @param client        Player's index.
	 * @return              Team index the client is on (mod specific).
	 * @error               Invalid client index, client not in game, or no mod support.
	 */
	static int GetClientTeam(int client)
	{
		return ExecFunc(s_GetClientTeamFunc, client);
	}

	/**
	 * @brief Sets a client's AdminId.
	 *
	 * @param client        Player's index.
	 * @param id            AdminId to set.  INVALID_ADMIN_ID removes admin permissions.
	 * @param temp          True if the id should be freed on disconnect.
	 * @error               Invalid client index, client not connected, or bogus AdminId.
	 */
	static void SetUserAdmin(int client, AdminId id, bool temp = false)
	{
		ExecFunc(s_SetUserAdminFunc, client, id, temp);
	}

	/**
	 * @brief Retrieves a client's AdminId.
	 *
	 * @param client        Player's index.
	 * @return              AdminId of the client, or INVALID_ADMIN_ID if none.
	 * @error               Invalid client index, or client not connected.
	 */
	static AdminId GetUserAdmin(int client)
	{
		return ExecFunc(s_GetUserAdminFunc, client);
	}

	/**
	 * @brief Sets access flags on a client.  If the client is not an admin,
	 * a temporary, anonymous AdminId is given.
	 *
	 * @param client        Player's index.
	 * @param args          Flags to set on the client.
	 * @error               Invalid client index, or client not connected.
	 */
	template<typename ... Args>
	static void AddUserFlags(int client, Args ... args)
	{
		PushArg(s_AddUserFlagsFunc, client);
		AddUserFlagsSub(args...);
	}
private:
	static void AddUserFlagsSub(AdminFlag flag)
	{
		ExecFunc(s_AddUserFlagsFunc, flag);
	}

	template<typename ... Args>
	static void AddUserFlagsSub(AdminFlag flag, Args ... args)
	{
		ExecFunc(s_AddUserFlagsFunc, flag);
		AddUserFlagsSub(args...);
	}
public:
	/**
	 * @brief Removes flags from a client.  If the client is not an admin,
	 * this has no effect.
	 *
	 * @param client        Player's index.
	 * @param args          Flags to remove from the client.
	 * @error               Invalid client index, or client not connected.
	 */
	template<typename ... Args>
	static void RemoveUserFlags(int client, Args ... args)
	{
		PushArg(s_RemoveUserFlagsFunc, client);
		RemoveUserFlagsSub(args...);
	}
private:
	static void RemoveUserFlagsSub(AdminFlag flag)
	{
		ExecFunc(s_RemoveUserFlagsFunc, flag);
	}

	template<typename ... Args>
	static void RemoveUserFlagsSub(AdminFlag flag, Args ... args)
	{
		ExecFunc(s_RemoveUserFlagsFunc, flag);
		AddUserFlagsSub(args...);
	}
public:
	/**
	 * @brief Sets access flags on a client using bits instead of flags.  If the
	 * client is not an admin, and flags not 0, a temporary, anonymous AdminId is given.
	 *
	 * @param client        Player's index.
	 * @param flags         Bitstring of flags to set on client.
	 */
	static void SetUserFlagBits(int client, int flags)
	{
		ExecFunc(s_SetUserFlagBitsFunc, client, flags);
	}

	/**
	 * @brief Returns client access flags.  If the client is not an admin,
	 * the result is always 0.
	 *
	 * @param client        Player's index.
	 * @return              Flags
	 * @error               Invalid client index, or client not connected.
	 */
	static int GetUserFlagBits(int client)
	{
		return ExecFunc(s_GetUserFlagBitsFunc, client);
	}

	/**
	 * @brief Returns whether a user can target another user.
	 * This is a helper function for CanAdminTarget.
	 *
	 * @param client        Player's index.
	 * @param target        Target player's index.
	 * @return              True if target is targettable by the player, false otherwise.
	 * @error               Invalid or unconnected player indexers.
	 */
	static bool CanUserTarget(int client, int target)
	{
		return ExecFunc(s_CanUserTargetFunc, client, target);
	}

	/**
	 * @brief Runs through the Core-defined admin authorization checks on a player.
	 * Has no effect if the player is already an admin.
	 *
	 * Note: This function is based on the internal cache only.
	 *
	 * @param client        Client index.
	 * @return              True if access was changed, false if it did not.
	 * @error               Invalid client index or client not in-game AND authorized.
	 */
	static bool RunAdminCacheChecks(int client)
	{
		return ExecFunc(s_RunAdminCacheChecksFunc, client);
	}

	/**
	 * @brief Signals that a player has completed post-connection admin checks.
	 * Has no effect if the player has already had this event signalled.
	 *
	 * Note: This must be sent even if no admin id was assigned.
	 *
	 * @param client        Client index.
	 * @error               Invalid client index or client not in-game AND authorized.
	 */
	static void NotifyPostAdminCheck(int client)
	{
		ExecFunc(s_NotifyPostAdminCheckFunc, client);
	}

	/**
	 * @brief Creates a fake client.
	 *
	 * @param name          Name to use.
	 * @return              Client index on success, 0 otherwise.
	 */
	static int CreateFakeClient(const char* name)
	{
		return ExecFunc(s_CreateFakeClientFunc, name);
	}

	/**
	 * @brief Sets a convar value on a fake client.
	 *
	 * @param client        Client index.
	 * @param cvar          ConVar name.
	 * @param value         ConVar value.
	 * @error               Invalid client index, client not connected,
	 *                      or client not a fake client.
	 */
	static void SetFakeClientConVar(int client, const char* cvar, const char* value)
	{
		ExecFunc(s_SetFakeClientConVarFunc, client, cvar, value);
	}

	/**
	 * @brief Returns the client's health.
	 *
	 * @param client        Player's index.
	 * @return              Health value.
	 * @error               Invalid client index, client not in game, or no mod support.
	 */
	static int GetClientHealth(int client)
	{
		return ExecFunc(s_GetClientHealthFunc, client);
	}

	/**
	 * @brief Returns the client's model name.
	 *
	 * @param client        Player's index.
	 * @param model         Buffer to store the client's model name.
	 * @param maxlen        Maximum length of string buffer (includes NULL terminator).
	 * @error               Invalid client index, client not in game, or no mod support.
	 */
	static void GetClientModel(int client, char* model, int maxlen)
	{
		PushArg(s_GetClientModelFunc, client);
		PushArg(s_GetClientModelFunc, model, maxlen);
		PushArg(s_GetClientModelFunc, maxlen);
		ExecFunc(s_GetClientModelFunc);
	}

	/**
	 * @brief Returns the client's weapon name.
	 *
	 * @param client        Player's index.
	 * @param weapon        Buffer to store the client's weapon name.
	 * @param maxlen        Maximum length of string buffer (includes NULL terminator).
	 * @error               Invalid client index, client not in game, or no mod support.
	 */
	static void GetClientWeapon(int client, char* weapon, int maxlen)
	{
		PushArg(s_GetClientWeaponFunc, client);
		PushArg(s_GetClientWeaponFunc, weapon, maxlen);
		PushArg(s_GetClientWeaponFunc, maxlen);
		ExecFunc(s_GetClientWeaponFunc);
	}

	/**
	 * @brief Returns the client's max size vector.
	 *
	 * @param client        Player's index.
	 * @param vec           Destination vector to store the client's max size.
	 * @error               Invalid client index, client not in game, or no mod support.
	 */
	static void GetClientMaxs(int client, float vec[3])
	{
		ExecFunc(s_GetClientMaxsFunc, client, vec);
	}

	/**
	 * @brief Returns the client's min size vector.
	 *
	 * @param client        Player's index.
	 * @param vec           Destination vector to store the client's min size.
	 * @error               Invalid client index, client not in game, or no mod support.
	 */
	static void GetClientMins(int client, float vec[3])
	{
		ExecFunc(s_GetClientMinsFunc, client, vec);
	}

	/**
	 * @brief Returns the client's position angle.
	 *
	 * @param client        Player's index.
	 * @param ang           Destination vector to store the client's position angle.
	 * @error               Invalid client index, client not in game, or no mod support.
	 */
	static void GetClientAbsAngles(int client, float ang[3])
	{
		PushArg(s_GetClientAbsAnglesFunc, client);
		PushArg(s_GetClientAbsAnglesFunc, ang, 3);
		ExecFunc(s_GetClientAbsAnglesFunc);
	}

	/**
	 * @brief Returns the client's origin vector.
	 *
	 * @param client        Player's index.
	 * @param vec           Destination vector to store the client's origin vector.
	 * @error               Invalid client index, client not in game, or no mod support.
	 */
	static void GetClientAbsOrigin(int client, float vec[3])
	{
		PushArg(s_GetClientAbsOriginFunc, client);
		PushArg(s_GetClientAbsOriginFunc, vec, 3);
		ExecFunc(s_GetClientAbsOriginFunc);
	}

	/**
	 * @brief Returns the client's armor.
	 *
	 * @param client        Player's index.
	 * @return              Armor value.
	 * @error               Invalid client index, client not in game, or no mod support.
	 */
	static int GetClientArmor(int client)
	{
		return ExecFunc(s_GetClientArmorFunc, client);
	}

	/**
	 * @brief Returns the client's death count.
	 *
	 * @param client        Player's index.
	 * @return              Death count.
	 * @error               Invalid client index, client not in game, or no mod support.
	 */
	static int GetClientDeaths(int client)
	{
		return ExecFunc(s_GetClientDeathsFunc, client);
	}

	/**
	 * @brief Returns the client's frag count.
	 *
	 * @param client        Player's index.
	 * @return              Frag count.
	 * @error               Invalid client index, client not in game, or no mod support.
	 */
	static int GetClientFrags(int client)
	{
		return ExecFunc(s_GetClientFragsFunc, client);
	}

	/**
	 * @brief Returns the client's send data rate in bytes/sec.
	 *
	 * @param client        Player's index.
	 * @return              Data rate.
	 * @error               Invalid client index, client not connected, or fake client.
	 */
	static int GetClientDataRate(int client)
	{
		return ExecFunc(s_GetClientDataRateFunc, client);
	}

	/**
	 * @brief Returns if a client is timing out
	 *
	 * @param client        Player's index.
	 * @return              True if client is timing out, false otherwise.
	 * @error               Invalid client index, client not connected, or fake client.
	 */
	static bool IsClientTimingOut(int client)
	{
		return ExecFunc(s_IsClientTimingOutFunc, client);
	}

	/**
	 * @brief Returns the client's connection time in seconds.
	 *
	 * @param client        Player's index.
	 * @return              Connection time.
	 * @error               Invalid client index, client not connected, or fake client.
	 */
	static float GetClientTime(int client)
	{
		return sp_ctof(ExecFunc(s_GetClientTimeFunc, client));
	}

	/**
	 * @brief Returns the client's current latency (RTT), more accurate than GetAvgLatency but jittering.
	 *
	 * @param client        Player's index.
	 * @param flow          Traffic flowing direction.
	 * @return              Latency, or -1 if network info is not available.
	 * @error               Invalid client index, client not connected, or fake client.
	 */
	static float GetClientLatency(int client, NetFlow flow)
	{
		return sp_ctof(ExecFunc(s_GetClientLatencyFunc, client, flow));
	}

	/**
	 * @brief Returns the client's average packet latency in seconds.
	 *
	 * @param client        Player's index.
	 * @param flow          Traffic flowing direction.
	 * @return              Latency, or -1 if network info is not available.
	 * @error               Invalid client index, client not connected, or fake client.
	 */
	static float GetClientAvgLatency(int client, NetFlow flow)
	{
		return sp_ctof(ExecFunc(s_GetClientAvgLatencyFunc, client, flow));
	}

	/**
	 * @brief Returns the client's average packet loss, values go from 0 to 1 (for percentages).
	 *
	 * @param client        Player's index.
	 * @param flow          Traffic flowing direction.
	 * @return              Average packet loss, or -1 if network info is not available.
	 * @error               Invalid client index, client not connected, or fake client.
	 */
	static float GetClientAvgLoss(int client, NetFlow flow)
	{
		return sp_ctof(ExecFunc(s_GetClientAvgLossFunc, client, flow));
	}

	/**
	 * @brief Returns the client's average packet choke, values go from 0 to 1 (for percentages).
	 *
	 * @param client        Player's index.
	 * @param flow          Traffic flowing direction.
	 * @return              Average packet loss, or -1 if network info is not available.
	 * @error               Invalid client index, client not connected, or fake client.
	 */
	static float GetClientAvgChoke(int client, NetFlow flow)
	{
		return sp_ctof(ExecFunc(s_GetClientAvgChokeFunc, client, flow));
	}

	/**
	 * @brief Returns the client's data flow in bytes/sec.
	 *
	 * @param client        Player's index.
	 * @param flow          Traffic flowing direction.
	 * @return              Data flow.
	 * @error               Invalid client index, client not connected, or fake client.
	 */
	static float GetClientAvgData(int client, NetFlow flow)
	{
		return sp_ctof(ExecFunc(s_GetClientAvgDataFunc, client, flow));
	}

	/**
	 * @brief Returns the client's average packet frequency in packets/sec.
	 *
	 * @param client        Player's index.
	 * @param flow          Traffic flowing direction.
	 * @return              Packet frequency.
	 * @error               Invalid client index, client not connected, or fake client.
	 */
	static float GetClientAvgPackets(int client, NetFlow flow)
	{
		return sp_ctof(ExecFunc(s_GetClientAvgPacketsFunc, client, flow));
	}

	/**
	 * @brief Translates an userid index to the real player index.
	 *
	 * @param userid        Userid value.
	 * @return              Client value.
	 * @error               Returns 0 if invalid userid.
	 */
	static int GetClientOfUserId(int userid)
	{
		return ExecFunc(s_GetClientOfUserIdFunc, userid);
	}

	/**
	 * @brief Disconnects a client from the server as soon as the next frame starts.
	 *
	 * Note: Originally, KickClient() was immediate.  The delay was introduced
	 * because despite warnings, plugins were using it in ways that would crash.
	 * The new safe version can break cases that rely on immediate disconnects,
	 * but ensures that plugins do not accidentally cause crashes.
	 *
	 * If you need immediate disconnects, use KickClientEx().
	 *
	 * Note: IsClientInKickQueue() will return true before the kick occurs.
	 *
	 * @param client        Client index.
	 * @param format        Optional formatting rules for disconnect reason.
	 *                      Note that a period is automatically appended to the string by the engine.
	 * @param args          Variable number of format parameters.
	 * @error               Invalid client index, or client not connected.
	 */
	template<typename ... Args>
	static void KickClient(int client, const char* format = "", Args ... args)
	{
		PushArg(s_KickClientFunc, client);
		PushArg(s_KickClientFunc, format);
		KickClientSub(args...);
	}
private:
	static void KickClientSub()
	{
		ExecFunc(s_KickClientFunc);
	}

	template<typename T, typename ... Args>
	static void KickClientSub(T arg, Args ... args)
	{
		PushArg(s_KickClientFunc, arg);
		KickClientSub(args...);
	}
public:
	/**
	 * @brief Immediately disconnects a client from the server.
	 *
	 * Kicking clients from certain events or callbacks may cause crashes.  If in
	 * doubt, create a short (0.1 second) timer to kick the client in the next
	 * available frame.
	 *
	 * @param client        Client index.
	 * @param format        Optional formatting rules for disconnect reason.
	 *                      Note that a period is automatically appended to the string by the engine.
	 * @param ...           Variable number of format parameters.
	 * @error               Invalid client index, or client not connected.
	 */
	template<typename ... Args>
	static void KickClientEx(int client, const char* format = "", Args ... args)
	{
		PushArg(s_KickClientExFunc, client);
		PushArg(s_KickClientExFunc, format);
		KickClientExSub(args...);
	}
private:
	static void KickClientExSub()
	{
		ExecFunc(s_KickClientExFunc);
	}

	template<typename T, typename ... Args>
	static void KickClientExSub(T arg, Args ... args)
	{
		PushArg(s_KickClientExFunc, arg);
		KickClientExSub(args...);
	}
public:
	/**
	 * @brief Changes a client's team through the mod's generic team changing function.
	 * On CS:S, this will kill the player.
	 *
	 * @param client        Client index.
	 * @param team          Mod-specific team index.
	 * @error               Invalid client index, client not in game, or lack of
	 *                      mod support.
	 */
	static void ChangeClientTeam(int client, int team)
	{
		ExecFunc(s_ChangeClientTeamFunc, client, team);
	}

	/**
	 * @brief Returns the clients unique serial identifier.
	 *
	 * @param client        Client index.
	 * @return              Serial number.
	 * @error               Invalid client index, or client not connected.
	 */
	static int GetClientSerial(int client)
	{
		return ExecFunc(s_GetClientSerialFunc, client);
	}

	/**
	 * @brief Returns the client index by its serial number.
	 *
	 * @param serial        Serial number.
	 * @return              Client index, or 0 for invalid serial.
	 */
	static int GetClientFromSerial(int serial)
	{
		return ExecFunc(s_GetClientFromSerialFunc, serial);
	}
