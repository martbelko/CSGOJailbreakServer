public:
	/**
	 * Get an entity's flags.
	 *
	 * @note The game's actual flags are internally translated by SM
	 *       to match the entity flags defined above as the actual values
	 *       can differ per engine.
	 *
	 * @param entity        Entity index.
	 * @return              Entity's flags, see entity flag defines above.
	 * @error               Invalid entity index, or lack of mod compliance.
	 */
	static int GetEntityFlags(int entity)
	{
		return ExecFunc(s_GetEntityFlagsFunc, entity);
	}

	/**
	 * Sets an entity's flags.
	 *
	 * @note The entity flags as defined above are internally translated by SM
	 *       to match the current game's expected value for the flags as
	 *       the actual values can differ per engine.
	 *
	 * @param entity        Entity index.
	 * @param flags         Entity flags, see entity flag defines above.
	 * @error               Invalid entity index, or lack of mod compliance.
	 */
	static void SetEntityFlags(int entity, int flags)
	{
		ExecFunc(s_SetEntityFlagsFunc, entity, flags);
	}

	/**
	 * Gets an entity's movetype.
	 *
	 * @param entity        Entity index.
	 * @return              Movetype, see enum above.
	 * @error               Invalid entity index, or lack of mod compliance.
	 */
	static MoveType GetEntityMoveType(int entity)
	{
		return static_cast<MoveType>(ExecFunc(s_GetEntityMoveTypeFunc, entity));
	}

	/**
	 * Sets an entity's movetype.
	 *
	 * @param entity        Entity index.
	 * @param moveType      Movetype, see enum above.
	 * @error               Invalid entity index, or lack of mod compliance.
	 */
	static void SetEntityMoveType(int entity, MoveType moveType)
	{
		ExecFunc(s_SetEntityMoveTypeFunc, entity, moveType);
	}

	/**
	 * Gets an entity's render mode.
	 *
	 * @param entity        Entity index.
	 * @return              RenderMode value.
	 * @error               Invalid entity index, or lack of mod compliance.
	 */
	static RenderMode GetEntityRenderMode(int entity)
	{
		return static_cast<RenderMode>(ExecFunc(s_GetEntityRenderModeFunc, entity));
	}

	/**
	 * Sets an entity's render mode.
	 *
	 * @param entity        Entity index.
	 * @param mode          RenderMode value.
	 * @error               Invalid entity index, or lack of mod compliance.
	 */
	static void SetEntityRenderMode(int entity, RenderMode mode)
	{
		ExecFunc(s_SetEntityRenderModeFunc, entity, mode);
	}

	/**
	 * Gets an entity's render Fx.
	 *
	 * @param entity        Entity index.
	 * @return              RenderFx value.
	 * @error               Invalid entity index, or lack of mod compliance.
	 */
	static RenderFx GetEntityRenderFx(int entity)
	{
		return static_cast<RenderFx>(ExecFunc(s_GetEntityRenderFxFunc, entity));
	}

	/**
	 * Sets an entity's render Fx.
	 *
	 * @param entity        Entity index.
	 * @param fx            RenderFx value.
	 * @error               Invalid entity index, or lack of mod compliance.
	 */
	static void SetEntityRenderFx(int entity, RenderFx fx)
	{
		ExecFunc(s_SetEntityRenderFxFunc, entity, fx);
	}

	/**
	 * Gets an entity's color.
	 *
	 * @param entity        Entity index.
	 * @param r             Amount of red (0-255)
	 * @param g             Amount of green (0-255)
	 * @param b             Amount of blue (0-255)
	 * @param a             Amount of alpha (0-255)
	 * @error               Invalid entity index, or lack of mod compliance.
	 */
	static void GetEntityRenderColor(int entity, int& r, int& g, int& b, int& a)
	{
		PushArg(s_GetEntityRenderColorFunc, entity);
		PushArgRef(s_GetEntityRenderColorFunc, r);
		PushArgRef(s_GetEntityRenderColorFunc, b);
		PushArgRef(s_GetEntityRenderColorFunc, b);
		PushArgRef(s_GetEntityRenderColorFunc, a);
		ExecFunc(s_GetEntityRenderColorFunc);
	}

	/**
	 * Sets an entity's color.
	 *
	 * @param entity        Entity index
	 * @param r             Amount of red (0-255)
	 * @param g             Amount of green (0-255)
	 * @param b             Amount of blue (0-255)
	 * @param a             Amount of alpha (0-255)
	 * @error               Invalid entity index, or lack of mod compliance.
	 */
	static void SetEntityRenderColor(int entity, int r = 255, int g = 255, int b = 255, int a = 255)
	{
		ExecFunc(s_SetEntityRenderColorFunc, entity, r, g, b, a);
	}

	/**
	 * Gets an entity's gravity.
	 *
	 * @param entity 	Entity index.
	 * @return              Entity's m_flGravity value.
	 * @error               Invalid entity index, or lack of mod compliance.
	 */
	static float GetEntityGravity(int entity)
	{
		return ExecFunc(s_GetEntityGravityFunc, entity);
	}

	/**
	 * Sets an entity's gravity.
	 *
	 * @param entity        Entity index.
	 * @param amount        Gravity to set (default = 1.0, half = 0.5, double = 2.0).
	 * @error               Invalid entity index, or lack of mod compliance.
	 */
	static void SetEntityGravity(int entity, float amount)
	{
		ExecFunc(s_SetEntityGravityFunc, entity, amount);
	}

	/**
	 * Sets an entity's health
	 *
	 * @param entity        Entity index.
	 * @param amount        Health amount.
	 * @error               Invalid entity index, or lack of mod compliance.
	 */
	static void SetEntityHealth(int entity, int amount)
	{
		ExecFunc(s_SetEntityHealthFunc, entity, amount);
	}

	/**
	 * Get's a users current pressed buttons
	 *
	 * @param client        Client index
	 * @return              Bitsum of buttons
	 * @error               Invalid client index, client not in game,
	 *                      or lack of mod compliance.
	 */
	static int GetClientButtons(int client)
	{
		return ExecFunc(s_GetClientButtonsFunc, client);
	}
