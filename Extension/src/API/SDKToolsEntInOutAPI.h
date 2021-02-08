public:
	/**
		 * @brief Invokes a named input method on an entity.
		 *
		 * After completion (successful or not), the current global variant is re-initialized.
		 *
		 * @param dest          Destination entity index.
		 * @param input         Input action.
		 * @param activator     Entity index which initiated the sequence of actions (-1 for a NULL entity).
		 * @param caller        Entity index from which this event is sent (-1 for a NULL entity).
		 * @param outputid      Unknown.
		 * @return              True if successful otherwise false.
		 * @error               Invalid entity index or no mod support.
		 */
	static bool AcceptEntityInput(int dest, const char* input, int activator = -1, int caller = -1, int outputid = 0)
	{
		return ExecFunc(s_AcceptEntityInputFunc, dest, input, activator, caller, outputid);
	}

	// SDKTOOLS_ENTOUTPUT.INC

	/**
	 * Add an entity output hook on a entity classname
	 *
	 * @param className     The classname to hook.
	 * @param output        The output name to hook.
	 * @param callback      An EntityOutput function pointer.
	 * @error               Entity Outputs disabled.
	 */
	static void HookEntityOutput(const char* className, const char* output, EntityOutputFunc callback)
	{
		std::string classNameStr = className;
		std::string outputStr = output;
		s_EntityOutputCallbacks[std::make_pair(classNameStr, outputStr)] = callback;
		ExecFunc(s_HookEntityOutputFunc, className, output);
	}

	/**
	 * Remove an entity output hook.
	 * @param className     The classname to hook.
	 * @param output        The output name to hook.
	 * @return              True on success, false if no valid hook was found.
	 * @error               Entity Outputs disabled.
	 */
	static bool UnhookEntityOutput(const char* className, const char* output)
	{
		return ExecFunc(s_UnhookEntityOutputFunc, className, output);
	}

	/**
	 * Add an entity output hook on a single entity instance
	 *
	 * @param entity        The entity on which to add a hook.
	 * @param output        The output name to hook.
	 * @param callback      An EntityOutput function pointer.
	 * @param once          Only fire this hook once and then remove itself.
	 * @error               Entity Outputs disabled or Invalid Entity index.
	 */
	static void HookSingleEntityOutput(int entity, const char* output, EntityOutputFunc callback, bool once = false)
	{
		std::string outputStr = output;
		s_SingleEntityOutputCallbacks[std::make_pair(entity, outputStr)] = callback;
		ExecFunc(s_HookSingleEntityOutputFunc, entity, output, once);
	}

	/**
	 * Remove a single entity output hook.
	 *
	 * @param entity        The entity on which to remove the hook.
	 * @param output        The output name to hook.
	 * @return              True on success, false if no valid hook was found.
	 * @error               Entity Outputs disabled or Invalid Entity index.
	 */
	static bool UnhookSingleEntityOutput(int entity, const char* output)
	{
		return ExecFunc(s_UnhookSingleEntityOutputFunc, entity, output);
	}

	/**
	 * Fire a named output on an entity.
	 *
	 * After completion (successful or not), the current global variant is re-initialized.
	 *
	 * @param caller        Entity index from where the output is fired.
	 * @param output        Output name.
	 * @param activator     Entity index which initiated the sequence of actions (-1 for a NULL entity).
	 * @param delay         Delay before firing the output.
	 * @error               Invalid entity index or no mod support.
	 */
	static void FireEntityOutput(int caller, const char* output, int activator = -1, float delay = 0.0f)
	{
		ExecFunc(s_FireEntityOutputFunc, caller, output, activator, delay);
	}
