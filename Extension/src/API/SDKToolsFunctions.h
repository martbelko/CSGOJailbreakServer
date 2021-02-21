public:
	/**
	 * Removes a player's item.
	 *
	 * @param client        Client index.
	 * @param item          CBaseCombatWeapon entity index.
	 * @return              True on success, false otherwise.
	 * @error               Invalid client or entity, lack of mod support, or client not in
	 *                      game.
	 */
	static bool RemovePlayerItem(int client, int item)
	{
		return ExecFunc(s_RemovePlayerItemFunc, client, item);
	}

	/**
	 * Gives a named item to a player.
	 *
	 * @param client        Client index.
	 * @param item          Item classname (such as weapon_ak47).
	 * @param iSubType      Unknown.
	 * @return              Entity index on success, or -1 on failure.
	 * @error               Invalid client or client not in game, or lack of mod support.
	 */
	static int GivePlayerItem(int client, const char* item, int iSubType = 0)
	{
		return ExecFunc(s_GivePlayerItemFunc, client, item, iSubType);
	}

	/**
	 * Returns the weapon in a player's slot.
	 *
	 * @param client        Client index.
	 * @param slot          Slot index (mod specific).
	 * @return              Entity index on success, -1 if no weapon existed.
	 * @error               Invalid client or client not in game, or lack of mod support.
	 */
	static int GetPlayerWeaponSlot(int client, int slot)
	{
		return ExecFunc(s_GetPlayerWeaponSlotFunc, client, slot);
	}

	/**
	 * Ignites an entity on fire.
	 *
	 * @param entity        Entity index.
	 * @param time          Number of seconds to set on fire.
	 * @param npc           True to only affect NPCs.
	 * @param size          Unknown.
	 * @param level         Unknown.
	 * @error               Invalid entity or client not in game, or lack of mod support.
	 */
	static void IgniteEntity(int entity, float time, bool npc = false, float size = 0.0, bool level = false)
	{
		ExecFunc(s_IgniteEntityFunc, entity, time, npc, size, level);
	}

	/**
	 * Extinguishes an entity that is on fire.
	 *
	 * @param entity        Entity index.
	 * @error               Invalid entity or client not in game, or lack of mod support.
	 */
	static void ExtinguishEntity(int entity)
	{
		ExecFunc(s_ExtinguishEntityFunc, entity);
	}

	/**
	 * Teleports an entity.
	 *
	 * @param entity        Client index.
	 * @param origin        New origin, or nullptr for no change.
	 * @param angles        New angles, or nullptr for no change.
	 * @param velocity      New velocity, or nullptr for no change.
	 * @error               Invalid entity or client not in game, or lack of mod support.
	 */
	static void TeleportEntity(int entity, const float origin[3] = nullptr, const float angles[3] = nullptr, const float velocity[3] = nullptr)
	{
		PushArg(s_TeleportEntityFunc, entity);

		if (origin == nullptr)
			s_TeleportEntityFunc->PushCell(NULL_VECTOR);
		else
			PushArg(s_TeleportEntityFunc, origin, 3);

		if (angles == nullptr)
			s_TeleportEntityFunc->PushCell(NULL_VECTOR);
		else
			PushArg(s_TeleportEntityFunc, angles, 3);

		if (velocity == nullptr)
			s_TeleportEntityFunc->PushCell(NULL_VECTOR);
		else
			PushArg(s_TeleportEntityFunc, velocity, 3);

		ExecFunc(s_TeleportEntityFunc);
	}

	/**
	 * Forces a player to commit suicide.
	 *
	 * @param client        Client index.
	 * @error               Invalid client or client not in game, or lack of mod support.
	 */
	static void ForcePlayerSuicide(int client)
	{
		ExecFunc(s_ForcePlayerSuicideFunc, client);
	}

	/**
	 * Slaps a player in a random direction.
	 *
	 * @param client        Client index.
	 * @param health        Health to subtract.
	 * @param sound         False to disable the sound effects.
	 * @error               Invalid client or client not in game, or lack of mod support.
	 */
	static void SlapPlayer(int client, int health = 5, bool sound = true)
	{
		ExecFunc(s_SlapPlayerFunc, client, health, sound);
	}

	/**
	 * Searches for an entity by classname.
	 *
	 * @param startEnt      The entity index after which to begin searching from.
	 *                      Use -1 to start from the first entity.
	 * @param className     Classname of the entity to find.
	 * @return              Entity index >= 0 if found, -1 otherwise.
	 * @error               Lack of mod support.
	 */
	static int FindEntityByClassname(int startEnt, const char* className)
	{
		return ExecFunc(s_FindEntityByClassnameFunc, startEnt, className);
	}

	/**
	 * Returns the client's eye angles.
	 *
	 * @param client        Player's index.
	 * @param ang           Destination vector to store the client's eye angles.
	 * @return              True on success, false on failure.
	 * @error               Invalid client index, client not in game, or no mod support.
	 */
	static bool GetClientEyeAngles(int client, float ang[3])
	{
		return ExecFunc(s_GetClientEyeAnglesFunc, client, ang);
	}

	/**
	 * Creates an entity by string name, but does not spawn it (see DispatchSpawn).
	 * If ForceEdictIndex is not -1, then it will use the edict by that index. If the index is
	 *  invalid or there is already an edict using that index, it will error out.
	 *
	 * @param className         Entity classname.
	 * @param forceEdictIndex   Edict index used by the created entity (ignored on Orangebox and above).
	 * @return                  Entity index on success, or -1 on failure.
	 * @error                   Invalid edict index, or no mod support.
	 */
	static int CreateEntityByName(const char* className, int forceEdictIndex = -1)
	{
		return ExecFunc(s_CreateEntityByNameFunc, className, forceEdictIndex);
	}

	/**
	 * Spawns an entity into the game.
	 *
	 * @param entity        Entity index of the created entity.
	 * @return              True on success, false otherwise.
	 * @error               Invalid entity index, or no mod support.
	 */
	static bool DispatchSpawn(int entity)
	{
		return ExecFunc(s_DispatchSpawnFunc, entity);
	}

	/**
	 * Dispatches a KeyValue into given entity using a string value.
	 *
	 * @param entity        Destination entity index.
	 * @param keyName       Name of the key.
	 * @param value         String value.
	 * @return              True on success, false otherwise.
	 * @error               Invalid entity index, or no mod support.
	 */
	static bool DispatchKeyValue(int entity, const char* keyName, const char* value)
	{
		return ExecFunc(s_DispatchKeyValueFunc, entity, keyName, value);
	}

	/**
	 * Dispatches a KeyValue into given entity using a floating point value.
	 *
	 * @param entity        Destination entity index.
	 * @param keyName       Name of the key.
	 * @param value         Floating point value.
	 * @return              True on success, false otherwise.
	 * @error               Invalid entity index, or no mod support.
	 */
	static bool DispatchKeyValueFloat(int entity, const char* keyName, float value)
	{
		return ExecFunc(s_DispatchKeyValueFloatFunc, entity, keyName, value);
	}

	/**
	 * Dispatches a KeyValue into given entity using a vector value.
	 *
	 * @param entity        Destination entity index.
	 * @param keyName       Name of the key.
	 * @param vec           Vector value.
	 * @return              True on success, false otherwise.
	 * @error               Invalid entity index, or no mod support.
	 */
	static bool DispatchKeyValueVector(int entity, const char* keyName, const float vec[3])
	{
		return ExecFunc(s_DispatchKeyValueVectorFunc, entity, keyName, vec);
	}

	/**
	 * Returns the entity a client is aiming at.
	 *
	 * @param client        Client performing the aiming.
	 * @param onlyClients   True to exclude all entities but clients.
	 * @return              Entity index being aimed at.
	 *                      -1 if no entity is being aimed at.
	 *                      -2 if the function is not supported.
	 * @error               Invalid client index or client not in game.
	 */
	static int GetClientAimTarget(int client, bool onlyClients = true)
	{
		return ExecFunc(s_GetClientAimTargetFunc, client, onlyClients);
	}

	/**
	 * Returns the total number of teams in a game.
	 * Note: This native should not be called before OnMapStart.
	 *
	 * @return              Total number of teams.
	 */
	static int GetTeamCount()
	{
		return ExecFunc(s_GetTeamCountFunc);
	}

	/**
	 * Retrieves the team name based on a team index.
	 * Note: This native should not be called before OnMapStart.
	 *
	 * @param index         Team index.
	 * @param name          Buffer to store string in.
	 * @param maxLength     Maximum length of string buffer.
	 * @error               Invalid team index.
	 */
	static void GetTeamName(int index, char* name, int maxLength)
	{
		PushArg(s_GetTeamNameFunc, index);
		s_GetTeamNameFunc->PushStringEx(name, maxLength, 0, 1);
		PushArg(s_GetTeamNameFunc, maxLength);
		ExecFunc(s_GetTeamNameFunc);
	}

	/**
	 * Returns the score of a team based on a team index.
	 * Note: This native should not be called before OnMapStart.
	 *
	 * @param teamIndex     Team index.
	 * @return              Score.
	 * @error               Invalid team index.
	 */
	static int GetTeamScore(int teamIndex)
	{
		return ExecFunc(s_GetTeamScoreFunc, teamIndex);
	}

	/**
	 * Sets the score of a team based on a team index.
	 * Note: This native should not be called before OnMapStart.
	 *
	 * @param teamIndex     Team index.
	 * @param score         New score value.
	 * @error               Invalid team index.
	 */
	static void SetTeamScore(int teamIndex, int score)
	{
		ExecFunc(s_SetTeamScoreFunc, teamIndex, score);
	}

	/**
	 * Retrieves the number of players in a certain team.
	 * Note: This native should not be called before OnMapStart.
	 *
	 * @param teamIndex     Team index.
	 * @return              Number of players in the team.
	 * @error               Invalid team index.
	 */
	static int GetTeamClientCount(int teamIndex)
	{
		return ExecFunc(s_GetTeamClientCountFunc, teamIndex);
	}

	/**
	 * Returns the entity index of a team.
	 *
	 * @param teamIndex     Team index.
	 * @return              Entity index of team.
	 * @error               Invalid team index.
	 */
	static int GetTeamEntity(int teamIndex)
	{
		return ExecFunc(s_GetTeamEntityFunc, teamIndex);
	}

	/**
	 * Sets the model to a given entity.
	 *
	 * @param entity        Entity index.
	 * @param model         Model name.
	 * @error               Invalid entity index, or no mod support.
	 */
	static void SetEntityModel(int entity, const char* model)
	{
		ExecFunc(s_SetEntityModelFunc, entity, model);
	}

	/**
	 * Retrieves the decal file name associated with a given client.
	 *
	 * @param client        Player's index.
	 * @param hex           Buffer to store the logo filename.
	 * @param maxLength     Maximum length of string buffer.
	 * @return              True on success, otherwise false.
	 * @error               Invalid client or client not in game.
	 */
	static bool GetPlayerDecalFile(int client, char* hex, int maxLength)
	{
		PushArg(s_GetPlayerDecalFileFunc, client);
		s_GetPlayerDecalFileFunc->PushStringEx(hex, maxLength, 0, 1);
		PushArg(s_GetPlayerDecalFileFunc, maxLength);
		return ExecFunc(s_GetPlayerDecalFileFunc);
	}

	/**
	 * Retrieves the jingle file name associated with a given client.
	 *
	 * @param client        Player's index.
	 * @param hex           Buffer to store the jingle filename.
	 * @param maxLength     Maximum length of string buffer.
	 * @return              True on success, otherwise false.
	 * @error               Invalid client or client not in game.
	 */
	static bool GetPlayerJingleFile(int client, char* hex, int maxLength)
	{
		PushArg(s_GetPlayerJingleFileFunc, client);
		s_GetPlayerJingleFileFunc->PushStringEx(hex, maxLength, 0, 1);
		PushArg(s_GetPlayerJingleFileFunc, maxLength);
		return ExecFunc(s_GetPlayerJingleFileFunc);
	}

	/**
	 * Returns the average server network traffic in bytes/sec.
	 *
	 * @param in            Buffer to store the input traffic velocity.
	 * @param out           Buffer to store the output traffic velocity.
	 */
	static void GetServerNetStats(float& inAmount, float& outAmount)
	{
		PushArgRef(s_GetServerNetStatsFunc, inAmount);
		PushArgRef(s_GetServerNetStatsFunc, outAmount);
		ExecFunc(s_GetServerNetStatsFunc);
	}

	/**
	 * Equip's a player's weapon.
	 *
	 * @param client        Client index.
	 * @param weapon        CBaseCombatWeapon entity index.
	 * @error               Invalid client or entity, lack of mod support, or client not in
	 *                      game.
	 */
	static void EquipPlayerWeapon(int client, int weapon)
	{
		ExecFunc(s_EquipPlayerWeaponFunc, client, weapon);
	}

	/**
	 * Activates an entity (CBaseAnimating::Activate)
	 *
	 * @param entity        Entity index.
	 * @error               Invalid entity or lack of mod support.
	 */
	static void ActivateEntity(int entity)
	{
		ExecFunc(s_ActivateEntityFunc, entity);
	}

	/**
	 * Sets values to client info buffer keys and notifies the engine of the change.
	 * The change does not get propagated to mods until the next frame.
	 *
	 * @param client        Player's index.
	 * @param key           Key string.
	 * @param value         Value string.
	 * @error               Invalid client index, or client not connected.
	 */
	static void SetClientInfo(int client, const char* key, const char* value)
	{
		ExecFunc(s_SetClientInfoFunc, client, key, value);
	}

	/**
	 * Changes a client's name.
	 *
	 * @param client        Player's index.
	 * @param name          New name.
	 * @error               Invalid client index, or client not connected.
	 */
	static void SetClientName(int client, const char* name)
	{
		ExecFunc(s_SetClientNameFunc, client, name);
	}

	/**
	 * Gives ammo of a certain type to a player.
	 * This natives obeys the maximum amount of ammo a player can carry per ammo type.
	 *
	 * @param client        The client index.
	 * @param amount        Amount of ammo to give. Is capped at ammotype's limit.
	 * @param ammotype      Type of ammo to give to player.
	 * @param suppressSound If true, don't play the ammo pickup sound.
	 * @return              Amount of ammo actually given.
	 */
	static int GivePlayerAmmo(int client, int amount, int ammotype, bool suppressSound = false)
	{
		return ExecFunc(s_GivePlayerAmmoFunc, client, amount, ammotype, suppressSound);
	}