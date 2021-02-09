public:
	/**
	 * Returns the calling plugin's Handle.
	 *
	 * @return              Handle of the calling plugin.
	 */
	static Handle GetMyHandle()
	{
		return ExecFunc(s_GetMyHandleFunc);
	}

	/**
	 * Returns an iterator that can be used to search through plugins.
	 *
	 * @return              Handle to iterate with.  Must be closed via
	 *                      CloseHandle().
	 * @error               Invalid Handle.
	 */
	static Handle GetPluginIterator()
	{
		return ExecFunc(s_GetPluginIteratorFunc);
	}

	/**
	 * Returns whether there are more plugins available in the iterator.
	 *
	 * @param iter          Handle to the plugin iterator.
	 * @return              True on more plugins, false otherwise.
	 * @error               Invalid Handle.
	 */
	static bool MorePlugins(Handle iter)
	{
		return ExecFunc(s_MorePluginsFunc, iter);
	}

	/**
	 * Returns the current plugin in the iterator and advances the iterator.
	 *
	 * @param iter          Handle to the plugin iterator.
	 * @return              Current plugin the iterator is at, before
	 *                      the iterator is advanced.
	 * @error               Invalid Handle.
	 */
	static Handle ReadPlugin(Handle iter)
	{
		return ExecFunc(s_ReadPluginFunc, iter);
	}

	/**
	 * Returns a plugin's status.
	 *
	 * @param plugin        Plugin Handle (INVALID_HANDLE uses the calling plugin).
	 * @return              Status code for the plugin.
	 * @error               Invalid Handle.
	 */
	static PluginStatus GetPluginStatus(Handle plugin)
	{
		return static_cast<PluginStatus>(ExecFunc(s_GetPluginStatusFunc, plugin));
	}

	/**
	 * Retrieves a plugin's file name relative to the plugins folder.
	 *
	 * @param plugin        Plugin Handle (INVALID_HANDLE uses the calling plugin).
	 * @param buffer        Buffer to the store the file name.
	 * @param maxlength     Maximum length of the name buffer.
	 * @error               Invalid Handle.
	 */
	static void GetPluginFilename(Handle plugin, char* buffer, int maxlength)
	{
		PushArg(s_GetPluginFilenameFunc, plugin);
		PushArg(s_GetPluginFilenameFunc, buffer, maxlength);
		PushArg(s_GetPluginFilenameFunc, maxlength);
		ExecFunc(s_GetPluginFilenameFunc);
	}

	/**
	 * Retrieves whether or not a plugin is being debugged.
	 *
	 * @param plugin        Plugin Handle (INVALID_HANDLE uses the calling plugin).
	 * @return              True if being debugged, false otherwise.
	 * @error               Invalid Handle.
	 */
	static bool IsPluginDebugging(Handle plugin)
	{
		return ExecFunc(s_IsPluginDebuggingFunc, plugin);
	}

	/**
	 * Retrieves a plugin's public info.
	 *
	 * @param plugin        Plugin Handle (INVALID_HANDLE uses the calling plugin).
	 * @param info          Plugin info property to retrieve.
	 * @param buffer        Buffer to store info in.
	 * @param maxlength     Maximum length of buffer.
	 * @return              True on success, false if property is not available.
	 * @error               Invalid Handle.
	 */
	static bool GetPluginInfo(Handle plugin, PluginInfo info, char* buffer, int maxlength)
	{
		PushArg(s_GetPluginInfoFunc, plugin);
		PushArg(s_GetPluginInfoFunc, info);
		PushArg(s_GetPluginInfoFunc, buffer, maxlength);
		PushArg(s_GetPluginInfoFunc, maxlength);
		return ExecFunc(s_GetPluginInfoFunc);
	}

	/**
	 * Finds a plugin by its order in the list from the "plugins list" server
	 * "sm" command.  You should not use this function to loop through all plugins,
	 * use the iterator instead.  Looping through all plugins using this native
	 * is O(n^2), whereas using the iterator is O(n).
	 *
	 * @param orderNum      Number of the plugin as it appears in "sm plugins list".
	 * @return              Plugin Handle on success, INVALID_HANDLE if no plugin
	 *                      matches the given number.
	 */
	static Handle FindPluginByNumber(int orderNum)
	{
		return ExecFunc(s_FindPluginByNumberFunc, orderNum);
	}

	/**
	 * Causes the plugin to enter a failed state.  An error will be thrown and
	 * the plugin will be paused until it is unloaded or reloaded.
	 *
	 * For backwards compatibility, if no extra arguments are passed, no
	 * formatting is applied.  If one or more additional arguments is passed,
	 * the string is formatted using Format().  If any errors are encountered
	 * during formatting, both the format specifier string and an additional
	 * error message are written.
	 *
	 * This function does not return, and no further code in the plugin is
	 * executed.
	 *
	 * @param string        Format specifier string.
	 * @param args          Formatting arguments.
	 * @error               Always throws SP_ERROR_ABORT.
	 */
	template<typename ... Args>
	static void SetFailState(const char* string, Args ... args)
	{
		PushArg(s_SetFailStateFunc, string);
		SetFailStateSub(args...);
	}
private:
	static void SetFailStateSub()
	{
		ExecFunc(s_SetFailStateFunc);
	}

	template<typename T, typename ... Args>
	static void SetFailStateSub(T arg, Args ... args)
	{
		PushArg(s_SetFailStateFunc, arg);
		SetFailStateSub(args...);
	}
public:
	/**
	 * Aborts the current callback and throws an error.  This function
	 * does not return in that no code is executed following it.
	 *
	 * @param fmt           String format.
	 * @param args          Format arguments.
	 * @error               Always!
	 */
	template<typename ... Args>
	static void ThrowError(const char* fmt, Args ... args)
	{
		PushArg(s_ThrowErrorFunc, fmt);
		ThrowErrorSub(args...);
	}
private:
	static void ThrowErrorSub()
	{
		ExecFunc(s_ThrowErrorFunc);
	}

	template<typename T, typename ... Args>
	static void ThrowErrorSub(T arg, Args ... args)
	{
		PushArg(s_ThrowErrorFunc, arg);
		ThrowErrorSub(args...);
	}
public:
	/**
	 * Logs a stack trace from the current function call. Code
	 * execution continues after the call
	 *
	 * @param fmt           Format string to send with the stack trace.
	 * @param args          Format arguments.
	 * @error               Always logs a stack trace.
	 */
	template<typename ... Args>
	static void LogStackTrace(const char* fmt, Args ... args)
	{
		PushArg(s_LogStackTraceFunc, fmt);
		LogStackTraceSub(args...);
	}
private:
	static void LogStackTraceSub()
	{
		ExecFunc(s_LogStackTraceFunc);
	}

	template<typename T, typename ... Args>
	static void LogStackTraceSub(T arg, Args ... args)
	{
		PushArg(s_LogStackTraceFunc, arg);
		LogStackTraceSub(args...);
	}
public:
	/**
	 * Gets the system time as a unix timestamp.
	 *
	 * @param bigStamp      Optional array to store the 64bit timestamp in.
	 * @return              32bit timestamp (number of seconds since unix epoch).
	 */
	static int GetTime(int bigStamp[2] = IVEC_2)
	{
		PushArg(s_GetTimeFunc, bigStamp, 2);
		return ExecFunc(s_GetTimeFunc);
	}

	/**
	 * Produces a date and/or time string value for a timestamp.
	 *
	 * See this URL for valid parameters:
	 * http://cplusplus.com/reference/clibrary/ctime/strftime.html
	 *
	 * Note that available parameters depends on support from your operating system.
	 * In particular, ones highlighted in yellow on that page are not currently
	 * available on Windows and should be avoided for portable plugins.
	 *
	 * @param buffer        Destination string buffer.
	 * @param maxlength     Maximum length of output string buffer.
	 * @param format        Formatting rules (passing NULL_STRING will use the rules defined in sm_datetime_format).
	 * @param stamp         Optional time stamp.
	 * @error               Buffer too small or invalid time format.
	 */
	static void FormatTime(char* buffer, int maxlength, const char* format, int stamp = -1)
	{
		PushArg(s_FormatTimeFunc, buffer, maxlength);
		PushArg(s_FormatTimeFunc, maxlength);
		PushArg(s_FormatTimeFunc, format);
		PushArg(s_FormatTimeFunc, stamp);
		ExecFunc(s_FormatTimeFunc);
	}

	/**
	 * Loads a game config file.
	 *
	 * @param file          File to load.  The path must be relative to the 'gamedata' folder under the config folder
	 *                      and the extension should be omitted.
	 * @return              A handle to the game config file or INVALID_HANDLE on failure.
	 */
	static GameDataHandle LoadGameConfigFile(const char* file)
	{
		return ExecFunc(s_LoadGameConfigFileFunc, file);
	}

	/**
	 * Returns an offset value.
	 *
	 * @param gc            Game config handle.
	 * @param key           Key to retrieve from the offset section.
	 * @return              An offset, or -1 on failure.
	 */
	static int GameConfGetOffset(Handle gc, const char* key)
	{
		return ExecFunc(s_GameConfGetOffsetFunc, gc, key);
	}

	/**
	 * Gets the value of a key from the "Keys" section.
	 *
	 * @param gc            Game config handle.
	 * @param key           Key to retrieve from the Keys section.
	 * @param buffer        Destination string buffer.
	 * @param maxlen        Maximum length of output string buffer.
	 * @return              True if key existed, false otherwise.
	 */
	static bool GameConfGetKeyValue(Handle gc, const char* key, char* buffer, int maxlen)
	{
		PushArg(s_GameConfGetKeyValueFunc, gc);
		PushArg(s_GameConfGetKeyValueFunc, key);
		PushArg(s_GameConfGetKeyValueFunc, buffer, maxlen);
		PushArg(s_GameConfGetKeyValueFunc, maxlen);
		return ExecFunc(s_GameConfGetKeyValueFunc);
	}

	/**
	 * Finds an address calculation in a GameConfig file,
	 * performs LoadFromAddress on it as appropriate, then returns the final address.
	 *
	 * @param gameconf      Game config handle.
	 * @param name          Name of the property to find.
	 * @return              An address calculated on success, or 0 on failure.
	 */
	static Address GameConfGetAddress(Handle gameconf, const char* name)
	{
		return ExecFunc(s_GameConfGetAddressFunc, gameconf, name);
	}

	/**
	 * Returns the operating system's "tick count," which is a number of
	 * milliseconds since the operating system loaded.  This can be used
	 * for basic benchmarks.
	 *
	 * @return              Tick count in milliseconds.
	 */
	static int GetSysTickCount()
	{
		return ExecFunc(s_GetSysTickCountFunc);
	}

	/**
	 * Specifies that the given config file should be executed after plugin load.
	 * OnConfigsExecuted() will not be called until the config file has executed,
	 * but it will be called if the execution fails.
	 *
	 * @param autoCreate    If true, and the config file does not exist, such a config
	 *                      file will be automatically created and populated with
	 *                      information from the plugin's registered cvars.
	 * @param name          Name of the config file, excluding the .cfg extension.
	 *                      If empty, <plugin.filename.cfg> is assumed.
	 * @param folder        Folder under cfg/ to use.  By default this is "sourcemod."
	 */
	static void AutoExecConfig(bool autoCreate = true, const char* name = "", const char* folder = "sourcemod")
	{
		ExecFunc(s_AutoExecConfigFunc, autoCreate, name, folder);
	}

	/**
	 * Registers a library name for identifying as a dependency to
	 * other plugins.
	 *
	 * @param name          Library name.
	 */
	static void RegPluginLibrary(const char* name)
	{
		ExecFunc(s_RegPluginLibraryFunc, name);
	}

	/**
	 * Returns whether a library exists.  This function should be considered
	 * expensive; it should only be called on plugin to determine availability
	 * of resources.  Use OnLibraryAdded()/OnLibraryRemoved() to detect changes
	 * in libraries.
	 *
	 * @param name          Library name of a plugin or extension.
	 * @return              True if exists, false otherwise.
	 */
	static bool LibraryExists(const char* name)
	{
		return ExecFunc(s_LibraryExistsFunc, name);
	}

	/**
	 * Returns the status of an extension, by filename.
	 *
	 * @param name          Extension name (like "sdktools.ext").
	 * @param error         Optional error message buffer.
	 * @param maxlength     Length of optional error message buffer.
	 * @return              -2 if the extension was not found.
	 *                      -1 if the extension was found but failed to load.
	 *                      0 if the extension loaded but reported an error.
	 *                      1 if the extension is running without error.
	 */
	static int GetExtensionFileStatus(const char* name, char* error = "", int maxlength = 0)
	{
		PushArg(s_GetExtensionFileStatusFunc, name);
		PushArg(s_GetExtensionFileStatusFunc, error, maxlength);
		PushArg(s_GetExtensionFileStatusFunc, maxlength);
		return ExecFunc(s_GetExtensionFileStatusFunc);
	}

	/**
	 * Loads a map list to an ADT Array.
	 *
	 * A map list is a list of maps from a file.  SourceMod allows easy configuration of
	 * maplists through addons/sourcemod/configs/maplists.cfg.  Each entry is given a
	 * name and a file (for example, "rtv" => "rtv.cfg"), or a name and a redirection
	 * (for example, "rtv" => "default").  This native will read a map list entry,
	 * cache the file, and return the list of maps it holds.
	 *
	 * Serial change numbers are used to identify if a map list has changed.  Thus, if
	 * you pass a serial change number and it's equal to what SourceMod currently knows
	 * about the map list, then SourceMod won't re-parse the file.
	 *
	 * If the maps end up being read from the maps folder (MAPLIST_FLAG_MAPSFOLDER), they
	 * are automatically sorted in alphabetical, ascending order.
	 *
	 * Arrays created by this function are temporary and must be freed via CloseHandle().
	 * Modifying arrays created by this function will not affect future return values or
	 * or the contents of arrays returned to other plugins.
	 *
	 * @param array         Array to store the map list.  If INVALID_HANDLE, a new blank
	 *                      array will be created.  The blocksize should be at least 16;
	 *                      otherwise results may be truncated.  Items are added to the array
	 *                      as strings.  The array is never checked for duplicates, and it is
	 *                      not read beforehand.  Only the serial number is used to detect
	 *                      changes.
	 * @param serial        Serial number to identify last known map list change.  If -1, the
	 *                      the value will not be checked.  If the map list has since changed,
	 *                      the serial is updated (even if -1 was passed).  If there is an error
	 *                      finding a valid maplist, then the serial is set to -1.
	 * @param str           Config name, or "default" for the default map list.  Config names
	 *                      should be somewhat descriptive.  For example, the admin menu uses
	 *                      a config name of "admin menu".  The list names can be configured
	 *                      by users in addons/sourcemod/configs/maplists.cfg.
	 * @param flags         MAPLIST_FLAG flags.
	 * @return              On failure:
	 *                      INVALID_HANDLE is returned, the serial is set to -1, and the input
	 *                      array (if any) is left unchanged.
	 *                      On no change:
	 *                      INVALID_HANDLE is returned, the serial is unchanged, and the input
	 *                      array (if any) is left unchanged.
	 *                      On success:
	 *                      A valid array Handle is returned, containing at least one map string.
	 *                      If an array was passed, the return value is equal to the passed Array
	 *                      Handle.  If the passed array was not cleared, it will have grown by at
	 *                      least one item.  The serial number is updated to a positive number.
	 * @error               Invalid array Handle that is not INVALID_HANDLE.
	 */
	static Handle ReadMapList(Handle arr = INVALID_HANDLE, int& serial = MINUS_ONE, const char* str = "default",
		int flags = MAPLIST_FLAG_CLEARARRAY)
	{
		PushArg(s_ReadMapListFunc, arr);
		PushArgRef(s_ReadMapListFunc, serial);
		PushArg(s_ReadMapListFunc, str);
		PushArg(s_ReadMapListFunc, flags);
		return ExecFunc(s_ReadMapListFunc);
	}

	/**
	 * Makes a compatibility binding for map lists.  For example, if a function previously used
	 * "clam.cfg" for map lists, this function will insert a "fake" binding to "clam.cfg" that
	 * will be overridden if it's in the maplists.cfg file.
	 *
	 * @param name          Configuration name that would be used with ReadMapList().
	 * @param file          Default file to use.
	 */
	static void SetMapListCompatBind(const char* name, const char* file)
	{
		ExecFunc(s_SetMapListCompatBindFunc, name, file);
	}

	/**
	 * Returns whether "GetFeatureStatus" will work. Using this native
	 * or this function will not cause SourceMod to fail loading on older versions,
	 * however, GetFeatureStatus will only work if this function returns true.
	 *
	 * @return              True if GetFeatureStatus will work, false otherwise.
	 */
	static bool CanTestFeatures()
	{
		return LibraryExists("__CanTestFeatures__");
	}

	/**
	 * Returns whether a feature exists, and if so, whether it is usable.
	 *
	 * @param type          Feature type.
	 * @param name          Feature name.
	 * @return              Feature status.
	 */
	static FeatureStatus GetFeatureStatus(FeatureType type, const char* name)
	{
		return static_cast<FeatureStatus>(ExecFunc(s_GetFeatureStatusFunc, type, name));
	}

	/**
	 * Requires that a given feature is available. If it is not, SetFailState()
	 * is called with the given message.
	 *
	 * @param type          Feature type.
	 * @param name          Feature name.
	 * @param fmt           Message format string, or empty to use default.
	 * @param args          Message format parameters, if any.
	 */
	template<typename ... Args>
	static void RequireFeature(FeatureType type, const char* name, const char* fmt = "", Args ... args)
	{
		PushArg(s_RequireFeatureFunc, type);
		PushArg(s_RequireFeatureFunc, name);
		PushArg(s_RequireFeatureFunc, fmt);
		RequireFeatureSub(args...);
	}
private:
	static void RequireFeatureSub()
	{
		ExecFunc(s_RequireFeatureFunc);
	}

	template<typename T, typename ... Args>
	static void RequireFeatureSub(T arg, Args ... args)
	{
		PushArg(s_RequireFeatureFunc, arg);
		RequireFeatureSub(args...);
	}
public:
	/**
	 * Load up to 4 bytes from a memory address.
	 *
	 * @param addr          Address to a memory location.
	 * @param size          How many bytes should be read.
	 *                      If loading a floating-point value, use NumberType_Int32.
	 * @return              The value that is stored at that address.
	 */
	template<typename any>
	static any LoadFromAddress(Address addr, NumberType size)
	{
		return static_cast<any>(ExecFunc(s_LoadFromAddressFunc, addr, size));
	}

	/**
	 * Store up to 4 bytes to a memory address.
	 *
	 * @param addr          Address to a memory location.
	 * @param data          Value to store at the address.
	 * @param size          How many bytes should be written.
	 *                      If storing a floating-point value, use NumberType_Int32.
	 */
	template<typename any>
	static void StoreToAddress(Address addr, any data, NumberType size)
	{
		ExecFunc(s_StoreToAddressFunc, addr, data, size);
	}
