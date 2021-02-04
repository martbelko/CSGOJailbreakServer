public:
	static void HookEvent(EventHookCallback callback, const char* name, EventHookMode mode)
	{
		if (mode == EventHookMode::EventHookMode_Pre)
			s_EventHookCallbacksPre[name] = callback;
		else if (mode == EventHookMode::EventHookMode_PostNoCopy)
			s_EventHookCallbacksPostNoCopy[name] = callback;
		else
		{
			s_EventHookCallbacksPost[name] = callback;
			mode = EventHookMode::EventHookMode_Post;
		}

		ExecFunc(s_HookEventFunc, name, mode);
	}

	static bool HookEventEx(EventHookCallback callback, const char* name, EventHookMode mode)
	{
		if (mode == EventHookMode::EventHookMode_Pre)
			s_EventHookCallbacksPre[name] = callback;
		else if (mode == EventHookMode::EventHookMode_PostNoCopy)
			s_EventHookCallbacksPostNoCopy[name] = callback;
		else
		{
			s_EventHookCallbacksPost[name] = callback;
			mode = EventHookMode::EventHookMode_Post;
		}

		return ExecFunc(s_HookEventExFunc, name, mode);
	}

	static void UnhookEvent(const char* name, EventHookMode mode) { ExecFunc(s_UnhookEventFunc, name, mode); }

	static EventHandle CreateEvent(const char* name, bool force) { return ExecFunc(s_CreateEventFunc, name, force); }

	static void FireEvent(Handle eventHandle, bool dontBroadcast) { ExecFunc(s_FireEventFunc, eventHandle, dontBroadcast); }

	static void CancelCreatedEvent(Handle eventHandle) { ExecFunc(s_CancelCreatedEventFunc, eventHandle); }

	static bool GetEventBool(Handle eventHandle, const char* key, bool defValue) { return ExecFunc(s_GetEventBoolFunc, eventHandle, key, defValue); }

	static void SetEventBool(Handle eventHandle, const char* key, bool value) { ExecFunc(s_SetEventBoolFunc, eventHandle, key, value); }

	static int GetEventInt(Handle eventHandle, const char* key, int defValue) { return ExecFunc(s_GetEventIntFunc, eventHandle, key, defValue); }

	static void SetEventInt(Handle eventHandle, const char* key, int value) { ExecFunc(s_SetEventIntFunc, eventHandle, key, value); }

	static float GetEventFloat(Handle eventHandle, const char* key, float defValue) { return ExecFunc(s_GetEventFloatFunc, eventHandle, key, defValue); }

	static void SetEventFloat(Handle eventHandle, const char* key, float value) { ExecFunc(s_SetEventFloatFunc, eventHandle, key, value); }

	static void GetEventString(Handle eventHandle, const char* key, char* value, int maxlength, const char* defValue) { ExecFunc(s_GetEventStringFunc, eventHandle, key, value, maxlength, defValue); }

	static void SetEventString(Handle eventHandle, const char* key, const char* value) { ExecFunc(s_SetEventStringFunc, eventHandle, key, value); }

	static void GetEventName(Handle eventHandle, char* name, int maxlength) { ExecFunc(s_GetEventNameFunc, eventHandle, name, maxlength); }

	static void SetEventBroadcast(Handle eventHandle, bool dontBroadcast) { ExecFunc(s_SetEventBroadcastFunc, eventHandle, dontBroadcast); }
