public:
	static void SDKHook(int entity, SDKHookType type, SDKHooksCallback1Func callback)
	{
		s_SDKHooksCallbacks[std::make_pair(entity, type)] = callback;
		ExecFunc(s_SDKHookFunc, entity, type);
	}
	static void SDKHook(int entity, SDKHookType type, SDKHooksCallback2Func callback)
	{
		s_SDKHooksCallbacks[std::make_pair(entity, type)] = callback;
		ExecFunc(s_SDKHookFunc, entity, type);
	}
	static void SDKHook(int entity, SDKHookType type, SDKHooksCallback3Func callback)
	{
		s_SDKHooksCallbacks[std::make_pair(entity, type)] = callback;
		ExecFunc(s_SDKHookFunc, entity, type);
	}
	static void SDKHook(int entity, SDKHookType type, SDKHooksCallback4Func callback)
	{
		s_SDKHooksCallbacks[std::make_pair(entity, type)] = callback;
		ExecFunc(s_SDKHookFunc, entity, type);
	}
	static void SDKHook(int entity, SDKHookType type, SDKHooksCallback5Func callback)
	{
		s_SDKHooksCallbacks[std::make_pair(entity, type)] = callback;
		ExecFunc(s_SDKHookFunc, entity, type);
	}
	static void SDKHook(int entity, SDKHookType type, SDKHooksCallback6Func callback)
	{
		s_SDKHooksCallbacks[std::make_pair(entity, type)] = callback;
		ExecFunc(s_SDKHookFunc, entity, type);
	}
	static void SDKHook(int entity, SDKHookType type, SDKHooksCallback7Func callback)
	{
		s_SDKHooksCallbacks[std::make_pair(entity, type)] = callback;
		ExecFunc(s_SDKHookFunc, entity, type);
	}
	static void SDKHook(int entity, SDKHookType type, SDKHooksCallback8Func callback)
	{
		s_SDKHooksCallbacks[std::make_pair(entity, type)] = callback;
		ExecFunc(s_SDKHookFunc, entity, type);
	}
	static void SDKHook(int entity, SDKHookType type, SDKHooksCallback9Func callback)
	{
		s_SDKHooksCallbacks[std::make_pair(entity, type)] = callback;
		ExecFunc(s_SDKHookFunc, entity, type);
	}
	static void SDKHook(int entity, SDKHookType type, SDKHooksCallback10Func callback)
	{
		s_SDKHooksCallbacks[std::make_pair(entity, type)] = callback;
		ExecFunc(s_SDKHookFunc, entity, type);
	}
	static void SDKHook(int entity, SDKHookType type, SDKHooksCallback11Func callback)
	{
		s_SDKHooksCallbacks[std::make_pair(entity, type)] = callback;
		ExecFunc(s_SDKHookFunc, entity, type);
	}
	static void SDKHook(int entity, SDKHookType type, SDKHooksCallback12Func callback)
	{
		s_SDKHooksCallbacks[std::make_pair(entity, type)] = callback;
		ExecFunc(s_SDKHookFunc, entity, type);
	}
	static void SDKHook(int entity, SDKHookType type, SDKHooksCallback13Func callback)
	{
		s_SDKHooksCallbacks[std::make_pair(entity, type)] = callback;
		ExecFunc(s_SDKHookFunc, entity, type);
	}
	static void SDKHook(int entity, SDKHookType type, SDKHooksCallback14Func callback)
	{
		s_SDKHooksCallbacks[std::make_pair(entity, type)] = callback;
		ExecFunc(s_SDKHookFunc, entity, type);
	}
	static void SDKHook(int entity, SDKHookType type, SDKHooksCallback15Func callback)
	{
		s_SDKHooksCallbacks[std::make_pair(entity, type)] = callback;
		ExecFunc(s_SDKHookFunc, entity, type);
	}

	static bool SDKHookEx(int entity, SDKHookType type, SDKHooksCallback1Func callback)
	{
		s_SDKHooksCallbacks[std::make_pair(entity, type)] = callback;
		return ExecFunc(s_SDKHookExFunc, entity, type);
	}
	static bool SDKHookEx(int entity, SDKHookType type, SDKHooksCallback2Func callback)
	{
		s_SDKHooksCallbacks[std::make_pair(entity, type)] = callback;
		return ExecFunc(s_SDKHookExFunc, entity, type);
	}
	static bool SDKHookEx(int entity, SDKHookType type, SDKHooksCallback3Func callback)
	{
		s_SDKHooksCallbacks[std::make_pair(entity, type)] = callback;
		return ExecFunc(s_SDKHookExFunc, entity, type);
	}
	static bool SDKHookEx(int entity, SDKHookType type, SDKHooksCallback4Func callback)
	{
		s_SDKHooksCallbacks[std::make_pair(entity, type)] = callback;
		return ExecFunc(s_SDKHookExFunc, entity, type);
	}
	static bool SDKHookEx(int entity, SDKHookType type, SDKHooksCallback5Func callback)
	{
		s_SDKHooksCallbacks[std::make_pair(entity, type)] = callback;
		return ExecFunc(s_SDKHookExFunc, entity, type);
	}
	static bool SDKHookEx(int entity, SDKHookType type, SDKHooksCallback6Func callback)
	{
		s_SDKHooksCallbacks[std::make_pair(entity, type)] = callback;
		return ExecFunc(s_SDKHookExFunc, entity, type);
	}
	static bool SDKHookEx(int entity, SDKHookType type, SDKHooksCallback7Func callback)
	{
		s_SDKHooksCallbacks[std::make_pair(entity, type)] = callback;
		return ExecFunc(s_SDKHookExFunc, entity, type);
	}
	static bool SDKHookEx(int entity, SDKHookType type, SDKHooksCallback8Func callback)
	{
		s_SDKHooksCallbacks[std::make_pair(entity, type)] = callback;
		return ExecFunc(s_SDKHookExFunc, entity, type);
	}
	static bool SDKHookEx(int entity, SDKHookType type, SDKHooksCallback9Func callback)
	{
		s_SDKHooksCallbacks[std::make_pair(entity, type)] = callback;
		return ExecFunc(s_SDKHookExFunc, entity, type);
	}
	static bool SDKHookEx(int entity, SDKHookType type, SDKHooksCallback10Func callback)
	{
		s_SDKHooksCallbacks[std::make_pair(entity, type)] = callback;
		return ExecFunc(s_SDKHookExFunc, entity, type);
	}
	static bool SDKHookEx(int entity, SDKHookType type, SDKHooksCallback11Func callback)
	{
		s_SDKHooksCallbacks[std::make_pair(entity, type)] = callback;
		return ExecFunc(s_SDKHookExFunc, entity, type);
	}
	static bool SDKHookEx(int entity, SDKHookType type, SDKHooksCallback12Func callback)
	{
		s_SDKHooksCallbacks[std::make_pair(entity, type)] = callback;
		return ExecFunc(s_SDKHookExFunc, entity, type);
	}
	static bool SDKHookEx(int entity, SDKHookType type, SDKHooksCallback13Func callback)
	{
		s_SDKHooksCallbacks[std::make_pair(entity, type)] = callback;
		return ExecFunc(s_SDKHookExFunc, entity, type);
	}
	static bool SDKHookEx(int entity, SDKHookType type, SDKHooksCallback14Func callback)
	{
		s_SDKHooksCallbacks[std::make_pair(entity, type)] = callback;
		return ExecFunc(s_SDKHookExFunc, entity, type);
	}
	static bool SDKHookEx(int entity, SDKHookType type, SDKHooksCallback15Func callback)
	{
		s_SDKHooksCallbacks[std::make_pair(entity, type)] = callback;
		return ExecFunc(s_SDKHookExFunc, entity, type);
	}

	static void SDKUnhook(int entity, SDKHookType type)
	{
		ExecFunc(s_SDKUnhookFunc, entity, type);
	}

	/**
	 * @brief Applies damage to an entity
	 *
	 * @note Force application is dependent on game and damage type(s)
	 *
	 * @param entity         Entity index taking damage
	 * @param inflictor      Inflictor entity index
	 * @param attacker       Attacker entity index
	 * @param damage         Amount of damage
	 * @param damageType     Bitfield of damage types
	 * @param weapon         Weapon index (orangebox and later) or -1 for unspecified
	 * @param damageForce    Velocity of damage force
	 * @param damagePosition Origin of damage
	 */
	static void SDKHooks_TakeDamage(int entity, int inflictor, int attacker, float damage,
		int damageType = DMG_GENERIC, int weapon = -1, const float damageForce[3] = nullptr,
		const float damagePosition[3] = nullptr)
	{
		PushArg(s_SDKHooks_TakeDamageFunc, entity);
		PushArg(s_SDKHooks_TakeDamageFunc, inflictor);
		PushArg(s_SDKHooks_TakeDamageFunc, attacker);
		PushArg(s_SDKHooks_TakeDamageFunc, damage);
		PushArg(s_SDKHooks_TakeDamageFunc, damageType);
		PushArg(s_SDKHooks_TakeDamageFunc, weapon);
		if (damageForce)
			PushArg(s_SDKHooks_TakeDamageFunc, damageForce, 3);
		else
			PushArg(s_SDKHooks_TakeDamageFunc, NULL_VECTOR);

		if (damagePosition)
			PushArg(s_SDKHooks_TakeDamageFunc, damagePosition, 3);
		else
			PushArg(s_SDKHooks_TakeDamageFunc, NULL_VECTOR);

		ExecFunc(s_SDKHooks_TakeDamageFunc);
	}

	/**
	 * @brief Forces a client to drop the specified weapon
	 *
	 * @param client        Client index.
	 * @param weapon        Weapon entity index.
	 * @param vecTarget     Location to toss weapon to, or nullptr for default.
	 * @param vecVelocity   Velocity at which to toss weapon, or nullptr for default.
	 * @error               Invalid client or weapon entity, weapon not owned by client.
	 */
	static void SDKHooks_DropWeapon(int client, int weapon,
		const float vecTarget[3] = nullptr, const float vecVelocity[3] = nullptr)
	{
		PushArg(s_SDKHooks_DropWeaponFunc, client);
		PushArg(s_SDKHooks_DropWeaponFunc, weapon);
		if (vecTarget)
			PushArg(s_SDKHooks_DropWeaponFunc, vecTarget);
		else
			PushArg(s_SDKHooks_DropWeaponFunc, NULL_VECTOR);

		if (vecVelocity)
			PushArg(s_SDKHooks_DropWeaponFunc, vecVelocity);
		else
			PushArg(s_SDKHooks_DropWeaponFunc, NULL_VECTOR);

		ExecFunc(s_SDKHooks_DropWeaponFunc);

	}
