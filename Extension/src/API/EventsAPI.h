public:
	/**
	 * @brief Creates a hook for when a game event is fired.
	 *
	 * @param name          Name of event.
	 * @param callback      An EventHook function pointer.
	 * @param mode          Optional EventHookMode determining the type of hook.
	 * @error               Invalid event name or invalid callback function.
	 */
	static void HookEvent(const char* name, EventHookCallback callback, EventHookMode mode = EventHookMode_Post)
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

	/**
	 * @brief Creates a hook for when a game event is fired.
	 *
	 * @param name          Name of event.
	 * @param callback      An EventHook function pointer.
	 * @param mode          Optional EventHookMode determining the type of hook.
	 * @return              True if event exists and was hooked successfully, false otherwise.
	 * @error               Invalid callback function.
	 */
	static bool HookEventEx(const char* name, EventHookCallback callback, EventHookMode mode = EventHookMode_Post)
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

	/**
	 * @brief Removes a hook for when a game event is fired.
	 *
	 * @param name          Name of event.
	 * @param callback      An EventHook function pointer.
	 * @param mode          Optional EventHookMode determining the type of hook.
	 * @error               Invalid callback function or no active hook for specified event.
	 */
	static void UnhookEvent(const char* name, EventHookMode mode = EventHookMode_Post)
	{
		ExecFunc(s_UnhookEventFunc, name, mode);
	}

	/**
	 * @brief Creates a game event to be fired later.
	 *
	 * The Handle should not be closed via CloseHandle().  It must be closed via
	 * event.Fire() or event.Cancel().
	 *
	 * @param name          Name of event.
	 * @param force         If set to true, this forces the event to be created even if it's not being hooked.
	 *                      Note that this will not force it if the event doesn't exist at all.
	 * @return              Handle to event. INVALID_HANDLE is returned if the event doesn't exist or isn't
	 *                      being hooked (unless force is true).
	 */
	static EventHandle CreateEvent(const char* name, bool force = false)
	{
		return ExecFunc(s_CreateEventFunc, name, force);
	}

	/**
	 * @brief Fires a game event.
	 *
	 * This function closes the event Handle after completing.
	 *
	 * @param event         Handle to the event.
	 * @param dontBroadcast Optional boolean that determines if event should be broadcast to clients.
	 * @error               Invalid or corrupt Handle.
	 */
	static void FireEvent(Handle eventHandle, bool dontBroadcast = false)
	{
		ExecFunc(s_FireEventFunc, eventHandle, dontBroadcast);
	}

	/**
	 * @brief Fires a game event.
	 *
	 * Unlike Fire, this function DOES NOT close the event Handle.
	 *
	 * @param event         Handle to the event.
	 * @param client        Index of client to receive the event.
	 */
	static void FireEventToClient(Handle eventHandle, int client)
	{
		ExecFunc(s_FireEventToClientFunc, eventHandle, client);
	}

	/**
	 * @brief Cancels a previously created game event that has not been fired.
	 *
	 * @param event         Handled to the event.
	 * @error               Invalid or corrupt Handle.
	 */
	static void CancelCreatedEvent(Handle eventHandle)
	{
		ExecFunc(s_CancelCreatedEventFunc, eventHandle);
	}

	/**
	 * @brief Returns the boolean value of a game event's key.
	 *
	 * @param event         Handle to the event.
	 * @param key           Name of event key.
	 * @param defValue      Optional default value to use if the key is not found.
	 * @return              The boolean value of the specified event key.
	 * @error               Invalid or corrupt Handle.
	 */
	static bool GetEventBool(Handle eventHandle, const char* key, bool defValue = false)
	{
		return ExecFunc(s_GetEventBoolFunc, eventHandle, key, defValue);
	}

	/**
	 * @brief Sets the boolean value of a game event's key.
	 *
	 * @param event         Handle to the event.
	 * @param key           Name of event key.
	 * @param value         New boolean value.
	 * @error               Invalid or corrupt Handle.
	 */
	static void SetEventBool(Handle eventHandle, const char* key, bool value)
	{
		ExecFunc(s_SetEventBoolFunc, eventHandle, key, value);
	}

	/**
	 * @brief Returns the integer value of a game event's key.
	 *
	 * @param event         Handle to the event.
	 * @param key           Name of event key.
	 * @param defValue      Optional default value to use if the key is not found.
	 * @return              The integer value of the specified event key.
	 * @error               Invalid or corrupt Handle.
	 */
	static int GetEventInt(Handle eventHandle, const char* key, int defValue = 0)
	{
		return ExecFunc(s_GetEventIntFunc, eventHandle, key, defValue);
	}

	/**
	 * @brief Sets the integer value of a game event's key.
	 *
	 * Integer value refers to anything that can be reduced to an integer.
	 * The various size specifiers, such as "byte" and "short" are still
	 * integers, and only refer to how much data will actually be sent
	 * over the network (if applicable).
	 *
	 * @param event         Handle to the event.
	 * @param key           Name of event key.
	 * @param value         New integer value.
	 * @error               Invalid or corrupt Handle.
	 */
	static void SetEventInt(Handle eventHandle, const char* key, int value)
	{
		ExecFunc(s_SetEventIntFunc, eventHandle, key, value);
	}

	/**
	 * @brief Returns the floating point value of a game event's key.
	 *
	 * @param event         Handle to the event.
	 * @param key           Name of event key.
	 * @param defValue      Optional default value to use if the key is not found.
	 * @return              The floating point value of the specified event key.
	 * @error               Invalid or corrupt Handle.
	 */
	static float GetEventFloat(Handle eventHandle, const char* key, float defValue = 0.0f)
	{
		return ExecFunc(s_GetEventFloatFunc, eventHandle, key, defValue);
	}

	/**
	 * @brief Sets the floating point value of a game event's key.
	 *
	 * @param event         Handle to the event.
	 * @param key           Name of event key.
	 * @param value         New floating point value.
	 * @error               Invalid or corrupt Handle.
	 */
	static void SetEventFloat(Handle eventHandle, const char* key, float value)
	{
		ExecFunc(s_SetEventFloatFunc, eventHandle, key, value);
	}

	/**
	 * @brief Retrieves the string value of a game event's key.
	 *
	 * @param event         Handle to the event.
	 * @param key           Name of event key.
	 * @param value         Buffer to store the value of the specified event key.
	 * @param maxlength     Maximum length of string buffer.
	 * @param defValue      Optional default value to use if the key is not found.
	 * @error               Invalid or corrupt Handle.
	 */
	static void GetEventString(Handle eventHandle, const char* key, char* value, int maxlength, const char* defValue = "")
	{
		PushArg(s_GetEventStringFunc, eventHandle);
		PushArg(s_GetEventStringFunc, key);
		PushArg(s_GetEventStringFunc, value, maxlength);
		PushArg(s_GetEventStringFunc, maxlength);
		PushArg(s_GetEventStringFunc, defValue);
		ExecFunc(s_GetEventStringFunc);
	}

	/**
	 * @brief Sets the string value of a game event's key.
	 *
	 * @param event         Handle to the event.
	 * @param key           Name of event key.
	 * @param value         New string value.
	 * @error               Invalid or corrupt Handle.
	 */
	static void SetEventString(Handle eventHandle, const char* key, const char* value)
	{
		ExecFunc(s_SetEventStringFunc, eventHandle, key, value);
	}

	/**
	 * @brief Retrieves the name of a game event.
	 *
	 * @param event         Handle to the event.
	 * @param name          Buffer to store the name of the event.
	 * @param maxlength     Maximum length of string buffer.
	 * @error               Invalid or corrupt Handle.
	 */
	static void GetEventName(Handle eventHandle, char* name, int maxlength)
	{
		PushArg(s_GetEventNameFunc, eventHandle);
		PushArg(s_GetEventNameFunc, name, maxlength);
		PushArg(s_GetEventNameFunc, maxlength);
		ExecFunc(s_GetEventNameFunc);
	}

	/**
	 * @brief Sets whether an event's broadcasting will be disabled or not.
	 *
	 * This has no effect on events Handles that are not from HookEvent
	 * or HookEventEx callbacks.
	 *
	 * @param event         Handle to an event from an event hook.
	 * @param dontBroadcast True to disable broadcasting, false otherwise.
	 * @error               Invalid Handle.
	 */
	static void SetEventBroadcast(Handle eventHandle, bool dontBroadcast)
	{
		ExecFunc(s_SetEventBroadcastFunc, eventHandle, dontBroadcast);
	}
