public:
	/**
	 * @brief Respawns a player.
	 *
	 * @param client        Player's index.
	 * @error               Invalid client index, client not in game.
	 */
	static void CS_RespawnPlayer(int client)
	{
		ExecFunc(s_CS_RespawnPlayerFunc, client);
	}

	/**
	 * @brief Switches the player's team.
	 *
	 * @param client        Player's index.
	 * @param team          Team index.
	 * @error               Invalid client index, client not in game.
	 */
	static void CS_SwitchTeam(int client, int team)
	{
		ExecFunc(s_CS_SwitchTeamFunc, client, team);
	}

	/**
	 * @brief Forces a player to drop or toss their weapon
	 *
	 * @param client        Player's index.
	 * @param weaponIndex   Index of weapon to drop.
	 * @param toss          True to toss weapon (with velocity) or false to just drop weapon
	 * @param blockhook     Set to true to stop the corresponding CS_OnCSWeaponDrop
	 * @error               Invalid client index, client not in game, or invalid weapon index.
	 */
	static void CS_DropWeapon(int client, int weaponIndex, bool toss, bool blockhook)
	{
		ExecFunc(s_CS_DropWeaponFunc, client, weaponIndex, toss, blockhook);
	}

	/**
	 * Forces round to end with a reason
	 *
	 * @param delay         Time (in seconds) to delay before new round starts
	 * @param reason        Reason for the round ending
	 * @param blockhook     Set to true to stop the corresponding CS_OnTerminateRound
	 *                      forward from being called.
	 */
	static void CS_TerminateRound(float delay, CSRoundEndReason reason, bool blockhook)
	{
		ExecFunc(s_CS_TerminateRoundFunc, delay, reason, blockhook);
	}

	/**
	 * Gets a weapon name from a weapon alias
	 *
	 * @param alias         Weapons alias to get weapon name for.
	 * @param weapon        Buffer to store weapons name
	 * @param size          Size of buffer to store the weapons name.
	 *
	 * @note Will set the buffer to the original alias if it is not an alias to a weapon.
	 */
	static void CS_GetTranslatedWeaponAlias(const char* alias, char* weapon, int size)
	{
		PushArg(s_CS_GetTranslatedWeaponAliasFunc, alias);
		PushArg(s_CS_GetTranslatedWeaponAliasFunc, weapon, size);
		PushArg(s_CS_GetTranslatedWeaponAliasFunc, size);
		ExecFunc(s_CS_GetTranslatedWeaponAliasFunc);
	}

	/**
	 * Gets a weapon's price
	 *
	 * @param client        Client to check weapon price for.
	 * @param id            Weapon id for the weapon to check
	 * @param defaultprice  Set to true to get defaultprice.
	 * @return              Returns price of the weapon (even if modified)
	 * @error               Invalid client, failing to get weapon info, or failing to get price offset.
	 *
	 * @note c4, knife and shield will always return 0. vest, vest helmet and night vision will always return default price.
	 */
	static int CS_GetWeaponPrice(int client, CSWeaponID id, bool defaultprice)
	{
		return ExecFunc(s_CS_GetWeaponPriceFunc, client, id, defaultprice);
	}

	/**
	 * Gets a clients clan tag
	 *
	 * @param client        Client index to get clan tag for.
	 * @param buffer        Buffer to store clients clan tag in.
	 * @param size          Size of the buffer.
	 * @return              Number of non-null bytes written.
	 * @error               Invalid client.
	 */
	static int CS_GetClientClanTag(int client, char* buffer, int size)
	{
		PushArg(s_CS_GetClientClanTagFunc, client);
		PushArg(s_CS_GetClientClanTagFunc, buffer, size);
		PushArg(s_CS_GetClientClanTagFunc, size);
		return ExecFunc(s_CS_GetClientClanTagFunc);
	}

	/**
	 * Sets a clients clan tag
	 *
	 * @param client        Client index to set clan tag for.
	 * @param tag           Tag to set clients clan tag as.
	 * @error               Invalid client.
	 */
	static void CS_SetClientClanTag(int client, const char* tag)
	{
		ExecFunc(s_CS_SetClientClanTagFunc, client, tag);
	}

	/**
	 * Gets a team's score
	 *
	 * @param team          Team index to get score for.
	 * @return              Returns the internal team score.
	 * @error               Invalid team index.
	 */
	static int CS_GetTeamScore(int team)
	{
		ExecFunc(s_CS_GetTeamScoreFunc, team);
	}

	/**
	 * Sets a team's score
	 *
	 * @param team          Team index to set score for.
	 * @param value         Value to set teams score as.
	 * @error               Invalid team index.
	 *
	 * @note This will update the scoreboard only after the scoreboard update function is called.
	 *       Use SetTeamScore plus this to update the scoreboard instantly and save values correctly.
	 */
	static void CS_SetTeamScore(int team, int value)
	{
		ExecFunc(s_CS_SetTeamScoreFunc, team, value);
	}

	/**
	 * Gets a client's mvp count
	 *
	 * @param client        Client index to get mvp count of.
	 * @return              Returns the client's internal MVP count.
	 * @error               Invalid client.
	 */
	static int CS_GetMVPCount(int client)
	{
		ExecFunc(s_CS_GetMVPCountFunc, client);
	}

	/**
	 * Sets a client's mvp count
	 *
	 * @param client        Client index to set mvp count for.
	 * @param value         Value to set client's mvp count as.
	 * @error               Invalid client.
	 */
	static void CS_SetMVPCount(int client, int value)
	{
		ExecFunc(s_CS_SetMVPCountFunc, client, value);
	}

	/**
	 * Gets a client's contribution score (CS:GO only)
	 *
	 * @param client        Client index to get score of.
	 * @return              Returns the client's score.
	 * @error               Invalid client.
	 */
	static int CS_GetClientContributionScore(int client)
	{
		return ExecFunc(s_CS_GetClientContributionScoreFunc, client);
	}

	/**
	 * Sets a client's contribution score (CS:GO only)
	 *
	 * @param client        Client index to set score for.
	 * @param value         Value to set client's score as.
	 * @error               Invalid client.
	 */
	static void CS_SetClientContributionScore(int client, int value)
	{
		ExecFunc(s_CS_SetClientContributionScoreFunc, client, value);
	}

	/**
	 * Gets a client's assists (CS:GO only)
	 *
	 * @param client        Client index to get assists of.
	 * @return              Returns the client's assists.
	 * @error               Invalid client.
	 */
	static int CS_GetClientAssists(int client)
	{
		ExecFunc(s_CS_GetClientAssistsFunc, client);
	}

	/**
	 * Sets a client's assists (CS:GO only)
	 *
	 * @param client        Client index to set assists for.
	 * @param value         Value to set client's assists as.
	 * @error               Invalid client.
	 */
	static void CS_SetClientAssists(int client, int value)
	{
		ExecFunc(s_CS_SetClientAssistsFunc, client, value);
	}

	/**
	 * Gets a weaponID from a alias
	 *
	 * @param alias         Weapon alias to attempt to get an id for.
	 * @return              Returns a weapon id or 0 if failed to find a match.
	 *
	 * @note For best results use CS_GetTranslatedWeaponAlias on the weapon name before passing it.
	 */
	static CSWeaponID CS_AliasToWeaponID(const char* alias)
	{
		return static_cast<CSWeaponID>(ExecFunc(s_CS_AliasToWeaponIDFunc, alias));
	}

	/**
	 * Gets a alias from a weaponID
	 *
	 * @param weaponID      WeaponID to get alias for.
	 * @param destination   Destination string to hold the weapon alias.
	 * @param len           Length of the destination array.
	 * @return              Returns number of cells written.
	 */
	static int CS_WeaponIDToAlias(CSWeaponID weaponID, char* destination, int len)
	{
		return ExecFunc(s_CS_WeaponIDToAliasFunc, weaponID, destination, len);
	}

	/**
	 * Returns weather a WeaponID is valid on the current mod (css or csgo)
	 *
	 * @param weaponID      WeaponID to check
	 * @return              Returns true if its a valid WeaponID false otherwise.
	 *
	 * @note This will return false always for CSWeapon_NONE. Should only be called after OnMapStart since weapon info isnt intialized before.
	 */
	static bool CS_IsValidWeaponID(CSWeaponID id)
	{
		return static_cast<bool>(ExecFunc(s_CS_IsValidWeaponIDFunc, id));
	}

	/**
	 * Sets a player's model based on their current class
	 *
	 * @param client        Player's index.
	 * @error               Invalid client index, client not in game.
	 */
	static void CS_UpdateClientModel(int client)
	{
		ExecFunc(s_CS_UpdateClientModelFunc, client);
	}

	/**
	 * Returns a CSWeaponID equivalent based on the item definition index.
	 *
	 * @param iDefIndex     Definition index to get the CSWeaponID value for.
	 * @return              Returns CSWeaponID value for the definition index.
	 * @error               Invalid definition index.
	 *
	 * @note In most cases the id will be the item definition index. Works for CS:GO ONLY.
	 */
	static CSWeaponID CS_ItemDefIndexToID(int iDefIndex)
	{
		return static_cast<CSWeaponID>(ExecFunc(s_CS_ItemDefIndexToIDFunc, iDefIndex));
	}

	/**
	 * Returns a item definition index equivalent based on the CSWeaponID.
	 *
	 * @param id            CSWeaponID to get the item definition for.
	 * @return              Returns item definition index value for the weapon id.
	 * @error               Invalid weapon id.
	 *
	 * @note In most cases the item deinition index will be the id. Works for CS:GO ONLY.
	 */
	static int CS_WeaponIDToItemDefIndex(CSWeaponID id)
	{
		return ExecFunc(s_CS_WeaponIDToItemDefIndexFunc, id);
	}
