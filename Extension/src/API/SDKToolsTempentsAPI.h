public:
	/**
	 * @brief Hooks a temp entity.
	 *
	 * @param teName        TE name to hook.
	 * @param hook          Function to use as a hook.
	 * @error               Temp Entity name not available or invalid function hook.
	 */
	static void AddTempEntHook(const char* teName, TEHookFunc hook)
	{
		std::string teNameStr = teName;
		s_TEHooksCallbacks[teNameStr] = hook;
		ExecFunc(s_AddTempEntHookFunc, teName);
	}

	/**
	 * @brief Removes a temp entity hook.
	 *
	 * @param teName        TE name to unhook.
	 * @param hook          Function used for the hook.
	 * @error               Temp Entity name not available or invalid function hook.
	 */
	static void RemoveTempEntHook(const char* teName)
	{
		ExecFunc(s_RemoveTempEntHookFunc, teName);
	}

	/**
	 * @brief Starts a temp entity transmission.
	 *
	 * @param teName        TE name.
	 * @error               Temp Entity name not available.
	 */
	static void TE_Start(const char* teName)
	{
		ExecFunc(s_TE_StartFunc, teName);
	}

	/**
	 * @brief Checks if a certain TE property exists.
	 *
	 * @param prop          Property to use.
	 * @return              True if the property exists, otherwise false.
	 */
	static bool TE_IsValidProp(const char* prop)
	{
		return ExecFunc(s_TE_IsValidPropFunc, prop);
	}

	/**
	 * @brief Sets an integer value in the current temp entity.
	 *
	 * @param prop          Property to use.
	 * @param value         Integer value to set.
	 * @error               Property not found.
	 */
	static void TE_WriteNum(const char* prop, int value)
	{
		ExecFunc(s_TE_WriteNumFunc, prop, value);
	}

	/**
	 * @brief Reads an integer value in the current temp entity.
	 *
	 * @param prop          Property to use.
	 * @return              Property value.
	 * @error               Property not found.
	 */
	static int TE_ReadNum(const char* prop)
	{
		return ExecFunc(s_TE_ReadVectorFunc, prop);
	}

	/**
	 * @brief Sets a floating point number in the current temp entity.
	 *
	 * @param prop          Property to use.
	 * @param value         Floating point number to set.
	 * @error               Property not found.
	 */
	static void TE_WriteFloat(const char* prop, float value)
	{
		ExecFunc(s_TE_WriteFloatFunc, prop, value);
	}

	/**
	 * @brief Reads a floating point number in the current temp entity.
	 *
	 * @param prop          Property to use.
	 * @return              Property value.
	 * @error               Property not found.
	 */
	static float TE_ReadFloat(const char* prop)
	{
		return ExecFunc(s_TE_ReadFloatFunc, prop);
	}

	/**
	 * @brief Sets a vector in the current temp entity.
	 *
	 * @param prop          Property to use.
	 * @param vector        Vector to set.
	 * @error               Property not found.
	 */
	static void TE_WriteVector(const char* prop, const float vector[3])
	{
		PushArg(s_TE_WriteVectorFunc, prop);
		PushArg(s_TE_WriteVectorFunc, vector, 3);
		ExecFunc(s_TE_WriteVectorFunc);
	}

	/**
	 * @brief Reads a vector in the current temp entity.
	 *
	 * @param prop          Property to use.
	 * @param vector        Vector to read.
	 * @error               Property not found.
	 */
	static void TE_ReadVector(const char* prop, float vector[3])
	{
		PushArg(s_TE_ReadVectorFunc, prop);
		PushArg(s_TE_ReadVectorFunc, vector, 3);
		ExecFunc(s_TE_ReadVectorFunc);
	}

	/**
	 * @brief Sets a QAngle in the current temp entity.
	 *
	 * @param prop          Property to use.
	 * @param angles        Angles to set.
	 * @error               Property not found.
	 */
	static void TE_WriteAngles(const char* prop, const float angles[3])
	{
		PushArg(s_TE_WriteAnglesFunc, prop);
		PushArg(s_TE_WriteAnglesFunc, angles, 3);
		ExecFunc(s_TE_WriteAnglesFunc);
	}

	/**
	 * @brief Sets an array of floats in the current temp entity.
	 *
	 * @param prop          Property to use.
	 * @param array         Array of values to copy.
	 * @param arraySize     Number of values to copy.
	 * @error               Property not found.
	 */
	static void TE_WriteFloatArray(const char* prop, const float arr[], int arraySize)
	{
		PushArg(s_TE_WriteFloatArrayFunc, prop);
		PushArg(s_TE_WriteFloatArrayFunc, arr, arraySize);
		PushArg(s_TE_WriteFloatArrayFunc, arraySize);
		ExecFunc(s_TE_WriteFloatArrayFunc);
	}

	/**
	 * @brief Sends the current temp entity to one or more clients.
	 *
	 * @param clients       Array containing player indexes to broadcast to.
	 * @param numClients    Number of players in the array.
	 * @param delay         Delay in seconds to send the TE.
	 * @error               Invalid client index or client not in game.
	 */
	static void TE_Send(const int clients[], int numClients, float delay = 0.0)
	{
		PushArg(s_TE_SendFunc, clients, numClients);
	}

	/**
	 * @brief Sets an encoded entity index in the current temp entity.
	 * (This is usually used for m_nStartEntity and m_nEndEntity).
	 *
	 * @param prop          Property to use.
	 * @param value         Value to set.
	 * @error               Property not found.
	 */
	static void TE_WriteEncodedEnt(const char* prop, int value)
	{
		int encvalue = (value & 0x0FFF) | ((1 & 0xF) << 12);
		TE_WriteNum(prop, encvalue);
	}

	/**
	 * @brief Broadcasts the current temp entity to all clients.
	 * @note See TE_Start().
	 *
	 * @param delay         Delay in seconds to send the TE.
	 */
	static void TE_SendToAll(float delay = 0.0)
	{
		int total = 0;
		int* clients = new int[s_MaxClients];
		for (int i = 1; i <= s_MaxClients; ++i)
			if (IsClientInGame(i))
				clients[total++] = i;
		TE_Send(clients, total, delay);
		delete[] clients;
	}

	/**
	 * @brief Sends the current TE to only a client.
	 * @note See TE_Start().
	 *
	 * @param client        Client to send to.
	 * @param delay         Delay in seconds to send the TE.
	 * @error               Invalid client index or client not in game.
	 */
	static void TE_SendToClient(int client, float delay = 0.0)
	{
		int players[1];
		players[0] = client;
		TE_Send(players, 1, delay);
	}

	/**
	 * @brief Sends the current TE to all clients that are in
	 * visible or audible range of the origin.
	 * @note See TE_Start().
	 * @note See GetClientsInRange()
	 *
	 * @param origin        Coordinates from which to test range.
	 * @param rangeType     Range type to use for filtering clients.
	 * @param delay         Delay in seconds to send the TE.
	 */
	static void TE_SendToAllInRange(float origin[3], ClientRangeType rangeType, float delay = 0.0f)
	{
		int* clients = new int[s_MaxClients];
		int total = GetClientsInRange(origin, rangeType, clients, s_MaxClients);
		TE_Send(clients, total, delay);
		delete[] clients;
	}
