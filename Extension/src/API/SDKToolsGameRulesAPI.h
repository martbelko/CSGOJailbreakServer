public:
	/**
		 * @brief Retrieves an integer value from a property of the gamerules entity.
		 *
		 * @param prop          Property name.
		 * @param size          Number of bytes to read (valid values are 1, 2, or 4).
		 *                      This value is auto-detected, and the size parameter is
		 *                      only used as a fallback in case detection fails.
		 * @param element       Element # (starting from 0) if property is an array.
		 * @return              Value at the given property offset.
		 * @error               Not supported.
		 */
	static int GameRules_GetProp(const char* prop, int size = 4, int element = 0)
	{
		return ExecFunc(s_GameRules_GetPropFunc, prop, size, element);
	}

	/**
	 * @brief Sets an integer value for a property of the gamerules entity.
	 *
	 * @param prop          Property name.
	 * @param value         Value to set.
	 * @param size          Number of bytes to write (valid values are 1, 2, or 4).
	 *                      This value is auto-detected, and the size parameter is
	 *                      only used as a fallback in case detection fails.
	 * @param element       Element # (starting from 0) if property is an array.
	 * @param changeState   This parameter is ignored.
	 * @error               Not supported.
	 */
	template<typename any>
	static void GameRules_SetProp(const char* prop, any value, int size = 4, int element = 0, bool changeState = false)
	{
		return ExecFunc(s_GameRules_SetPropFunc, prop, value, size, element, changeState);
	}

	/**
	 * @brief Retrieves a float value from a property of the gamerules entity.
	 *
	 * @param prop          Property name.
	 * @param element       Element # (starting from 0) if property is an array.
	 * @return              Value at the given property offset.
	 * @error               Not supported.
	 */
	static float GameRules_GetPropFloat(const char* prop, int element = 0)
	{
		return ExecFunc(s_GameRules_GetPropFloatFunc, prop, element);
	}

	/**
	 * @brief Sets a float value for a property of the gamerules entity.
	 *
	 * @param prop          Property name.
	 * @param value         Value to set.
	 * @param element       Element # (starting from 0) if property is an array.
	 * @param changeState   This parameter is ignored.
	 * @error               Not supported.
	 */
	static void GameRules_SetPropFloat(const char* prop, float value, int element = 0, bool changeState = false)
	{
		ExecFunc(s_GameRules_SetPropFloatFunc, prop, value, element, changeState);
	}

	/**
	 * @brief Retrieves a entity index from a property of the gamerules entity.
	 *
	 * @param prop          Property name.
	 * @param element       Element # (starting from 0) if property is an array.
	 * @return              Entity index at the given property.
	 *                      If there is no entity, or the entity is not valid,
	 *                      then -1 is returned.
	 * @error               Not supported.
	 */
	static int GameRules_GetPropEnt(const char* prop, int element = 0)
	{
		return ExecFunc(s_GameRules_GetPropEntFunc, prop, element);
	}

	/**
	 * @brief Sets an entity index for a property of the gamerules entity.
	 *
	 * @param prop          Property name.
	 * @param other         Entity index to set, or -1 to unset.
	 * @param element       Element # (starting from 0) if property is an array.
	 * @param changeState   This parameter is ignored.
	 * @error               Not supported.
	 */
	static void GameRules_SetPropEnt(const char* prop, int other, int element = 0, bool changeState = false)
	{
		ExecFunc(s_GameRules_SetPropEntFunc, prop, other, element, changeState);
	}

	/**
	 * @brief Retrieves a vector of floats from the gamerules entity, given a named network property.
	 *
	 * @param prop          Property name.
	 * @param vec           Vector buffer to store data in.
	 * @param element       Element # (starting from 0) if property is an array.
	 * @error               Not supported.
	 */
	static void GameRules_GetPropVector(const char* prop, float vec[3], int element = 0)
	{
		PushArg(s_GameRules_GetPropVectorFunc, prop);
		PushArg(s_GameRules_GetPropVectorFunc, vec, 3);
		PushArg(s_GameRules_GetPropVectorFunc, element);
		ExecFunc(s_GameRules_GetPropVectorFunc);
	}

	/**
	 * @brief Sets a vector of floats in the gamerules entity, given a named network property.
	 *
	 * @param prop          Property name.
	 * @param vec           Vector to set.
	 * @param element       Element # (starting from 0) if property is an array.
	 * @param changeState   This parameter is ignored.
	 * @error               Not supported.
	 */
	static void GameRules_SetPropVector(const char* prop, const float vec[3], int element = 0, bool changeState = false)
	{
		PushArg(s_GameRules_SetPropVectorFunc, prop);
		PushArg(s_GameRules_SetPropVectorFunc, vec, 3);
		PushArg(s_GameRules_SetPropVectorFunc, element);
		PushArg(s_GameRules_SetPropVectorFunc, changeState);
		ExecFunc(s_GameRules_SetPropVectorFunc);
	}

	/**
	 * @brief Gets a gamerules property as a string.
	 *
	 * @param prop          Property to use.
	 * @param buffer        Destination string buffer.
	 * @param maxlen        Maximum length of output string buffer.
	 * @return              Number of non-null bytes written.
	 * @error               Not supported.
	 */
	static int GameRules_GetPropString(const char* prop, char* buffer, int maxlen)
	{
		PushArg(s_GameRules_GetPropStringFunc, prop);
		PushArg(s_GameRules_GetPropStringFunc, buffer, maxlen);
		PushArg(s_GameRules_GetPropStringFunc, maxlen);
		return ExecFunc(s_GameRules_GetPropStringFunc);
	}

	/**
	 * @brief Sets a gamerules property as a string.
	 *
	 * @param prop          Property to use.
	 * @param buffer        String to set.
	 * @param changeState   This parameter is ignored.
	 * @return              Number of non-null bytes written.
	 * @error               Not supported.
	 */
	static int GameRules_SetPropString(const char* prop, const char* buffer, bool changeState = false)
	{
		return ExecFunc(s_GameRules_SetPropStringFunc, prop, buffer, changeState);
	}

	/**
	 * @brief Gets the current round state.
	 *
	 * @return              Round state.
	 * @error               Game doesn't support round state.
	 */
	static RoundState GameRules_GetRoundState()
	{
		return static_cast<RoundState>(GameRules_GetProp("m_iRoundState"));
	}
