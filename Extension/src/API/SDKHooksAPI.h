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
	static void SDKHooks_TakeDamage(int entity, int inflictor, int attacker, float damage, int damageType, int weapon, const float damageForce[3], const float damagePosition[3])
	{
		ExecFunc(s_SDKHooks_TakeDamageFunc, entity, inflictor, attacker, damage, damageType, weapon, damageForce, damagePosition);
	}
	static void SDKHooks_DropWeapon(int client, int weapon, const float vecTarget[3], const float vecVelocity[3])
	{
		ExecFunc(s_SDKHooks_DropWeaponFunc, client, weapon, vecTarget, vecVelocity);
	}
