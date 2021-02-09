public:
	/**
	 * @brief Sets the client to an inactive state waiting for a new map
	 *
	 * @param client        The client index
	 */
	static void InactivateClient(int client)
	{
		ExecFunc(s_InactivateClientFunc, client);
	}

	/**
	 * @brief Reconnect a client without dropping the netchannel
	 *
	 * @param client        The client index
	 */
	static void ReconnectClient(int client)
	{
		ExecFunc(s_ReconnectClientFunc, client);
	}
