public:
	/**
	 * Creates a new console variable.
	 *
	 * @param name          Name of new convar.
	 * @param defaultValue  String containing the default value of new convar.
	 * @param description   Optional description of the convar.
	 * @param flags         Optional bitstring of flags determining how the convar should be handled. See FCVAR_* constants for more details.
	 * @param hasMin        Optional boolean that determines if the convar has a minimum value.
	 * @param min           Minimum floating point value that the convar can have if hasMin is true.
	 * @param hasMax        Optional boolean that determines if the convar has a maximum value.
	 * @param max           Maximum floating point value that the convar can have if hasMax is true.
	 * @return              A handle to the newly created convar. If the convar already exists, a handle to it will still be returned.
	 * @error               Convar name is blank or is the same as an existing console command.
	 */
	static ConVarHandle CreateConVar(const char* name, const char* defaultValue, const char* description = "",
		int flags = 0, bool hasMin = false, float min = 0.0f, bool hasMax = false, float max = 0.0f)
	{
		return ExecFunc(s_CreateConVarFunc, name, defaultValue, description, flags, hasMin, min, hasMax, max);
	}

	/**
	 * Searches for a console variable.
	 *
	 * @param name          Name of convar to find.
	 * @return              A ConVar object if found; null otherwise.
	 */
	static ConVarHandle FindConVar(const char* name)
	{
		return ExecFunc(s_FindConVarFunc, name);
	}

	/**
		* Creates a hook for when a console variable's value is changed.
		*
		* @param convar        Handle to the convar.
		* @param callback      An OnConVarChanged function pointer.
		* @error               Invalid or corrupt Handle or invalid callback function.
		*/
	static void HookConVarChange(Handle convar, ConVarChangedFunc callback)
	{
		s_ConVarChangedCallbacks[convar] = callback;
		ExecFunc(s_HookConVarChangeFunc, convar);
	}

	/**
	 * Removes a hook for when a console variable's value is changed.
	 *
	 * @param convar        Handle to the convar.
	 * @error               Invalid or corrupt Handle, invalid callback function, or no active hook on convar.
	 */
	static void UnhookConVarChange(Handle convar)
	{
		ExecFunc(s_UnhookConVarChangeFunc, convar);
	}

	/**
	 * Returns the boolean value of a console variable.
	 *
	 * @param convar        Handle to the convar.
	 * @return              The boolean value of the convar.
	 * @error               Invalid or corrupt Handle.
	 */
	static bool GetConVarBool(Handle convar)
	{
		return ExecFunc(s_GetConVarBoolFunc, convar);
	}

	/**
	 * Sets the boolean value of a console variable.
	 *
	 * Note: The replicate and notify params are only relevant for the original, Dark Messiah, and
	 * Episode 1 engines. Newer engines automatically do these things when the convar value is changed.
	 *
	 * @param convar        Handle to the convar.
	 * @param value         New boolean value.
	 * @param replicate     If set to true, the new convar value will be set on all clients.
	 *                      This will only work if the convar has the FCVAR_REPLICATED flag
	 *                      and actually exists on clients.
	 * @param notify        If set to true, clients will be notified that the convar has changed.
	 *                      This will only work if the convar has the FCVAR_NOTIFY flag.
	 * @error               Invalid or corrupt Handle.
	 */
	static void SetConVarBool(Handle convar, bool value, bool replicate = false, bool notify = false)
	{
		ExecFunc(s_SetConVarBoolFunc, convar, value, replicate, notify);
	}

	/**
	 * Returns the integer value of a console variable.
	 *
	 * @param convar        Handle to the convar.
	 * @return              The integer value of the convar.
	 * @error               Invalid or corrupt Handle.
	 */
	static int GetConVarInt(Handle convar)
	{
		return ExecFunc(s_GetConVarIntFunc, convar);
	}

	/**
	 * Sets the integer value of a console variable.
	 *
	 * Note: The replicate and notify params are only relevant for the original, Dark Messiah, and
	 * Episode 1 engines. Newer engines automatically do these things when the convar value is changed.
	 *
	 * @param convar        Handle to the convar.
	 * @param value         New integer value.
	 * @param replicate     If set to true, the new convar value will be set on all clients.
	 *                      This will only work if the convar has the FCVAR_REPLICATED flag
	 *                      and actually exists on clients.
	 * @param notify        If set to true, clients will be notified that the convar has changed.
	 *                      This will only work if the convar has the FCVAR_NOTIFY flag.
	 * @error               Invalid or corrupt Handle.
	 */
	static void SetConVarInt(Handle convar, int value, bool replicate = false, bool notify = false)
	{
		ExecFunc(s_SetConVarIntFunc, convar, value, replicate, notify);
	}

	/**
	 * Returns the floating point value of a console variable.
	 *
	 * @param convar        Handle to the convar.
	 * @return              The floating point value of the convar.
	 * @error               Invalid or corrupt Handle.
	 */
	static float GetConVarFloat(Handle convar)
	{
		return ExecFunc(s_GetConVarFloatFunc, convar);
	}

	/**
	 * Sets the floating point value of a console variable.
	 *
	 * Note: The replicate and notify params are only relevant for the original, Dark Messiah, and
	 * Episode 1 engines. Newer engines automatically do these things when the convar value is changed.
	 *
	 * @param convar        Handle to the convar.
	 * @param value         New floating point value.
	 * @param replicate     If set to true, the new convar value will be set on all clients.
	 *                      This will only work if the convar has the FCVAR_REPLICATED flag
	 *                      and actually exists on clients.
	 * @param notify        If set to true, clients will be notified that the convar has changed.
	 *                      This will only work if the convar has the FCVAR_NOTIFY flag.
	 * @error               Invalid or corrupt Handle.
	 */
	static void SetConVarFloat(Handle convar, float value, bool replicate = false, bool notify = false)
	{
		ExecFunc(s_SetConVarFloatFunc, convar, value, replicate, notify);
	}

	/**
	 * Retrieves the string value of a console variable.
	 *
	 * @param convar        Handle to the convar.
	 * @param value         Buffer to store the value of the convar.
	 * @param maxlength     Maximum length of string buffer.
	 * @error               Invalid or corrupt Handle.
	 */
	static void GetConVarString(Handle convar, char* value, int maxlength)
	{
		PushArg(s_GetConVarStringFunc, convar);
		PushArg(s_GetConVarStringFunc, value, maxlength);
		PushArg(s_GetConVarStringFunc, maxlength);
		ExecFunc(s_GetConVarStringFunc);
	}

	/**
	 * Sets the string value of a console variable.
	 *
	 * Note: The replicate and notify params are only relevant for the original, Dark Messiah, and
	 * Episode 1 engines. Newer engines automatically do these things when the convar value is changed.
	 *
	 * @param convar        Handle to the convar.
	 * @param value         New string value.
	 * @param replicate     If set to true, the new convar value will be set on all clients.
	 *                      This will only work if the convar has the FCVAR_REPLICATED flag
	 *                      and actually exists on clients.
	 * @param notify        If set to true, clients will be notified that the convar has changed.
	 *                      This will only work if the convar has the FCVAR_NOTIFY flag.
	 * @error               Invalid or corrupt Handle.
	 */
	static void SetConVarString(Handle convar, const char* value, bool replicate = false, bool notify = false)
	{
		ExecFunc(s_SetConVarStringFunc, convar, value, replicate, notify);
	}

	/**
	 * Resets the console variable to its default value.
	 *
	 * Note: The replicate and notify params are only relevant for the original, Dark Messiah, and
	 * Episode 1 engines. Newer engines automatically do these things when the convar value is changed.
	 *
	 * @param convar        Handle to the convar.
	 * @param replicate     If set to true, the new convar value will be set on all clients.
	 *                      This will only work if the convar has the FCVAR_REPLICATED flag
	 *                      and actually exists on clients.
	 * @param notify        If set to true, clients will be notified that the convar has changed.
	 *                      This will only work if the convar has the FCVAR_NOTIFY flag.
	 * @error               Invalid or corrupt Handle.
	 */
	static void ResetConVar(Handle convar, bool replicate = false, bool notify = false)
	{
		ExecFunc(s_ResetConVarFunc, convar, replicate, notify);
	}

	/**
	 * Retrieves the default string value of a console variable.
	 *
	 * @param convar        Handle to the convar.
	 * @param value         Buffer to store the default value of the convar.
	 * @param maxlength     Maximum length of string buffer.
	 * @return              Number of bytes written to the buffer (UTF-8 safe).
	 * @error               Invalid or corrupt Handle.
	 */
	static int GetConVarDefault(Handle convar, char* value, int maxlength)
	{
		PushArg(s_GetConVarDefaultFunc, convar);
		PushArg(s_GetConVarDefaultFunc, value, maxlength);
		PushArg(s_GetConVarDefaultFunc, maxlength);
		return ExecFunc(s_GetConVarDefaultFunc);
	}

	/**
	 * Returns the bitstring of flags on a console variable.
	 *
	 * @param convar        Handle to the convar.
	 * @return              A bitstring containing the FCVAR_* flags that are enabled.
	 * @error               Invalid or corrupt Handle.
	 */
	static int GetConVarFlags(Handle convar)
	{
		return ExecFunc(s_GetConVarFlagsFunc, convar);
	}

	/**
	 * Sets the bitstring of flags on a console variable.
	 *
	 * @param convar        Handle to the convar.
	 * @param flags         A bitstring containing the FCVAR_* flags to enable.
	 * @error               Invalid or corrupt Handle.
	 */
	static void SetConVarFlags(Handle convar, int flags)
	{
		ExecFunc(s_SetConVarFlagsFunc, convar, flags);
	}

	/**
	 * Retrieves the specified bound of a console variable.
	 *
	 * @param convar        Handle to the convar.
	 * @param type          Type of bound to retrieve, ConVarBound_Lower or ConVarBound_Upper.
	 * @param value         By-reference cell to store the specified floating point bound value.
	 * @return              True if the convar has the specified bound set, false otherwise.
	 * @error               Invalid or corrupt Handle.
	 */
	static bool GetConVarBounds(Handle convar, ConVarBounds type, float& value)
	{
		PushArg(s_GetConVarBoundsFunc, convar);
		PushArg(s_GetConVarBoundsFunc, type);
		PushArgRef(s_GetConVarBoundsFunc, value);
		return ExecFunc(s_GetConVarBoundsFunc);
	}

	/**
	 * Sets the specified bound of a console variable.
	 *
	 * @param convar        Handle to the convar.
	 * @param type          Type of bound to set, ConVarBound_Lower or ConVarBound_Upper
	 * @param set           If set to true, convar will use specified bound. If false, bound will be removed.
	 * @param value         Floating point value to use as the specified bound.
	 * @error               Invalid or corrupt Handle.
	 */
	static void SetConVarBounds(Handle convar, ConVarBounds type, bool set, float value = 0.0f)
	{
		ExecFunc(s_SetConVarBoundsFunc, convar, type, set, value);
	}

	/**
	 * Retrieves the name of a console variable.
	 *
	 * @param convar        Handle to the convar.
	 * @param name          Buffer to store the name of the convar.
	 * @param maxlength     Maximum length of string buffer.
	 * @error               Invalid or corrupt Handle.
	 */
	static void GetConVarName(Handle convar, char* name, int maxlength)
	{
		PushArg(s_GetConVarNameFunc, convar);
		PushArg(s_GetConVarNameFunc, name, maxlength);
		PushArg(s_GetConVarNameFunc, maxlength);
		ExecFunc(s_GetConVarNameFunc);
	}

	/**
	 * Replicates a convar value to a specific client. This does not change the actual convar value.
	 *
	 * @param client        Client index
	 * @param convar        ConVar handle
	 * @param value         String value to send
	 * @return              True on success, false on failure
	 * @error               Invalid client index, client not in game, or client is fake
	 */
	static bool SendConVarValue(int client, Handle convar, const char* value)
	{
		return ExecFunc(s_SendConVarValueFunc, client, convar, value);
	}

	/**
	 * Starts a query to retrieve the value of a client's console variable.
	 *
	 * @param client        Player index.
	 * @param cvarName      Name of client convar to query.
	 * @param callback      A function to use as a callback when the query has finished.
	 * @param value         Optional value to pass to the callback function.
	 * @return              A cookie that uniquely identifies the query.
	 *                      Returns QUERYCOOKIE_FAILED on failure, such as when used on a bot.
	 */
	static QueryCookie QueryClientConVar(int client, const char* cvarName, ConVarQueryFinishedFunc callback, void* value = nullptr)
	{
		std::string cvarNameStr(cvarName);
		std::pair<int, std::string> pair = std::make_pair(client, cvarNameStr);
		s_ConVarFinishedCallbacks[pair] = callback;
		return static_cast<QueryCookie>(ExecFunc(s_QueryClientConVarFunc, client, cvarName, reinterpret_cast<int>(value)));
	}

	/**
	 * Returns true if the supplied character is valid in a ConVar name.
	 *
	 * @param c             Character to validate.
	 * @return              True is valid for ConVars, false otherwise
	 */
	static bool IsValidConVarChar(int c)
	{
		return (c == '_' || IsCharAlphaA(c) || isdigit(c));
	}