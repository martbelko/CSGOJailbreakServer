public:
	/**
	 * Sets a client's "viewing entity."
	 *
	 * @param client        Client index.
	 * @param entity        Entity index.
	 * @error               Invalid client or entity, lack of mod support, or client not in
	 *                      game.
	 */
	static void SetClientViewEntity(int client, int entity)
	{
		ExecFunc(s_SetClientViewEntityFunc, client, entity);
	}

	/**
	 * Sets a light style.
	 *
	 * @param style         Light style (from 0 to MAX_LIGHTSTYLES-1)
	 * @param value         Light value string (see world.cpp/light.cpp in dlls)
	 * @error               Light style index is out of range.
	 */
	static void SetLightStyle(int style, const char* value)
	{
		ExecFunc(s_SetLightStyleFunc, style, value);
	}

	/**
	 * Returns the client's eye position.
	 *
	 * @param client        Player's index.
	 * @param pos           Destination vector to store the client's eye position.
	 * @error               Invalid client index, client not in game, or no mod support.
	 */
	static void GetClientEyePosition(int client, float pos[3])
	{
		PushArg(s_GetClientEyePositionFunc, client);
		PushArg(s_GetClientEyePositionFunc, pos, 3);
		ExecFunc(s_GetClientEyePositionFunc);
	}
