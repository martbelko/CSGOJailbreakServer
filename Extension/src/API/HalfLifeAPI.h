public:
	/**
	 * @brief Logs a generic message to the HL2 logs.
	 *
	 * @param format        String format.
	 * @param ...           Format arguments.
	 */
	template<typename ... Args>
	static void LogToGame(const char* format, Args ... args)
	{
		PushArg(s_LogToGameFunc, format);
		LogToGameSub(args...);
	}
private:
	static void LogToGameSub()
	{
		ExecFunc(s_LogToGameFunc);
	}

	template<typename T, typename ... Args>
	static void LogToGameSub(T arg, Args ... args)
	{
		PushArgRef(s_LogToGameFunc, arg);
		LogToGameSub(args...);
	}
public:
	/**
	 * @brief Sets the seed value for the global Half-Life 2 Random Stream.
	 *
	 * @param seed         Seed value.
	 */
	static void SetRandomSeed(int seed)
	{
		ExecFunc(s_SetRandomSeedFunc, seed);
	}

	/**
	 * @brief Returns a random floating point number from the Half-Life 2 Random Stream.
	 *
	 * @param fMin          Minimum random bound.
	 * @param fMax          Maximum random bound.
	 * @return              A random number between (inclusive) fMin and fMax.
	 */
	static float GetRandomFloat(float fMin = 0.0, float fMax = 1.0)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<float> dis(fMin, fMax);
		return dis(gen);
	}

	/**
	 * @brief Returns a random number from the Half-Life 2 Random Stream.
	 *
	 * @param nmin          Minimum random bound.
	 * @param nmax          Maximum random bound.
	 * @return              A random number between (inclusive) nmin and nmax.
	 */
	static int GetRandomInt(int nmin, int nmax)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(nmin, nmax);
		return dis(gen);
	}

	/**
	 * @brief Returns whether a map is valid or not.
	 *
	 * @param map           Map name, excluding .bsp extension.
	 * @return              True if valid, false otherwise.
	 */
	static bool IsMapValid(const char* map)
	{
		return ExecFunc(s_IsMapValidFunc, map);
	}

	/**
	 * @brief Returns whether a full or partial map name is found or can be resolved
	 *
	 * @param map           Map name (usually same as map path relative to maps/ dir,
	 *                      excluding .bsp extension).
	 * @param foundmap      Resolved map name. If the return is FindMap_FuzzyMatch
	 *                      or FindMap_NonCanonical the buffer will be the full path.
	 * @param maxlen        Maximum length to write to map var.
	 * @return              Result of the find operation. Not all result types are supported on all games.
	 */
	static FindMapResult FindMap(const char* map, char* foundmap, int maxlen)
	{
		PushArg(s_FindMapFunc, map);
		PushArg(s_FindMapFunc, foundmap, maxlen);
		PushArg(s_FindMapFunc, maxlen);
		return static_cast<FindMapResult>(ExecFunc(s_FindMapFunc));
	}

	/**
	 * @brief Get the display name of a workshop map.
	 *
	 * Note: You do not need to call FindMap first.  This native will call FindMap internally.
	 *
	 * @param map           Map name (usually same as map path relative to maps/ dir,
	 *                      excluding .bsp extension).
	 * @param displayName   Map's display name, i.e. cp_mymapname or de_mymapname.
	 *                      If FindMap returns FindMap_PossiblyAvailable or FindMap_NotFound,
	 *                      the map cannot be resolved and this native will return false,
	 *                      but displayName will be a copy of map.
	 * @param maxlen        Maximum length to write to displayName var.
	 * @return              true if FindMap returns FindMap_Found, FindMap_FuzzyMatch, or
	 *                      FindMap_NonCanonical.
	 *                      false if FindMap returns FindMap_PossiblyAvailable or FindMap_NotFound.
	 */
	static bool GetMapDisplayName(const char* map, char* displayName, int maxlen)
	{
		PushArg(s_GetMapDisplayNameFunc, map);
		PushArg(s_GetMapDisplayNameFunc, displayName, maxlen);
		PushArg(s_GetMapDisplayNameFunc, maxlen);
		return ExecFunc(s_GetMapDisplayNameFunc);
	}

	/**
	 * @brief Returns whether the server is dedicated.
	 *
	 * @return              True if dedicated, false otherwise.
	 */
	static bool IsDedicatedServer()
	{
		return ExecFunc(s_IsDedicatedServerFunc);
	}

	/**
	 * @brief Returns a high-precision time value for profiling the engine.
	 *
	 * @return              A floating point time value.
	 */
	static float GetEngineTime()
	{
		return ExecFunc(s_GetEngineTimeFunc);
	}

	/**
	 * @brief Returns the game time based on the game tick.
	 *
	 * @return              Game tick time.
	 */
	static float GetGameTime()
	{
		return ExecFunc(s_GetGameTimeFunc);
	}

	/**
	 * @brief Returns the game's internal tick count.
	 *
	 * @return              Game tick count.
	 */
	static int GetGameTickCount()
	{
		return ExecFunc(s_GetGameTickCountFunc);
	}

	/**
	 * @brief Returns the time the Game took processing the last frame.
	 *
	 * @return              Game frame time.
	 */
	static float GetGameFrameTime()
	{
		return ExecFunc(s_GetGameFrameTimeFunc);
	}

	/**
	 * @brief Returns the game description from the mod.
	 *
	 * @param buffer        Buffer to store the description.
	 * @param maxlength     Maximum size of the buffer.
	 * @param original      If true, retrieves the original game description,
	 *                      ignoring any potential hooks from plugins.
	 * @return              Number of bytes written to the buffer (UTF-8 safe).
	 */
	static int GetGameDescription(char* buffer, int maxlength, bool original = false)
	{
		PushArg(s_GetGameDescriptionFunc, buffer, maxlength);
		PushArg(s_GetGameDescriptionFunc, maxlength);
		PushArg(s_GetGameDescriptionFunc, original);
		return ExecFunc(s_GetGameDescriptionFunc);
	}

	/**
	 * @brief Returns the name of the game's directory.
	 *
	 * @param buffer        Buffer to store the directory name.
	 * @param maxlength     Maximum size of the buffer.
	 * @return              Number of bytes written to the buffer (UTF-8 safe).
	 */
	static int GetGameFolderName(char* buffer, int maxlength)
	{
		PushArg(s_GetGameFolderNameFunc, buffer, maxlength);
		PushArg(s_GetGameFolderNameFunc, maxlength);
		return ExecFunc(s_GetGameFolderNameFunc);
	}

	/**
	 * @brief Returns the current map name.
	 *
	 * @param buffer        Buffer to store map name.
	 * @param maxlength     Maximum length of buffer.
	 * @return              Number of bytes written (UTF-8 safe).
	 */
	static int GetCurrentMap(char* buffer, int maxlength)
	{
		PushArg(s_GetCurrentMapFunc, buffer, maxlength);
		PushArg(s_GetCurrentMapFunc, maxlength);
		return ExecFunc(s_GetCurrentMapFunc);
	}

	/**
	 * @brief Precaches a given model.
	 *
	 * @param model         Name of the model to precache.
	 * @param preload       If preload is true the file will be precached before level startup.
	 * @return              Returns the model index, 0 for error.
	 */
	static int PrecacheModel(const char* model, bool preload = false)
	{
		return ExecFunc(s_PrecacheModelFunc, model, preload);
	}

	/**
	 * @brief Precaches a given sentence file.
	 *
	 * @param file          Name of the sentence file to precache.
	 * @param preload       If preload is true the file will be precached before level startup.
	 * @return              Returns a sentence file index.
	 */
	static int PrecacheSentenceFile(const char* file, bool preload = false)
	{
		return ExecFunc(s_PrecacheSentenceFileFunc, file, preload);
	}

	/**
	 * @brief Precaches a given decal.
	 *
	 * @param decal         Name of the decal to precache.
	 * @param preload       If preload is true the file will be precached before level startup.
	 * @return              Returns a decal index.
	 */
	static int PrecacheDecal(const char* decal, bool preload = false)
	{
		return ExecFunc(s_PrecacheDecalFunc, decal, preload);
	}

	/**
	 * @brief Precaches a given generic file.
	 *
	 * @param gen           Name of the generic file to precache.
	 * @param preload       If preload is true the file will be precached before level startup.
	 * @return              Returns a generic file index.
	 */
	static int PrecacheGeneric(const char* gen, bool preload = false)
	{
		return ExecFunc(s_PrecacheGenericFunc, gen, preload);
	}

	/**
	 * @brief Returns if a given model is precached.
	 *
	 * @param model         Name of the model to check.
	 * @return              True if precached, false otherwise.
	 */
	static bool IsModelPrecached(const char* model)
	{
		return ExecFunc(s_IsModelPrecachedFunc, model);
	}

	/**
	 * @brief Returns if a given decal is precached.
	 *
	 * @param decal         Name of the decal to check.
	 * @return              True if precached, false otherwise.
	 */
	static bool IsDecalPrecached(const char* decal)
	{
		return ExecFunc(s_IsDecalPrecachedFunc, decal);
	}

	/**
	 * @brief Returns if a given generic file is precached.
	 *
	 * @param gen           Name of the generic file to check.
	 * @return              True if precached, false otherwise.
	 */
	static bool IsGenericPrecached(const char* gen)
	{
		return ExecFunc(s_IsGenericPrecachedFunc, gen);
	}

	/**
	 * @brief Precaches a given sound.
	 *
	 * @param sound         Name of the sound to precache.
	 * @param preload       If preload is true the file will be precached before level startup.
	 * @return              True if successfully precached, false otherwise.
	 */
	static bool PrecacheSound(const char* sound, bool preload = false)
	{
		return ExecFunc(s_PrecacheSoundFunc, sound, preload);
	}

	/**
	 * @brief Creates different types of ingame messages.
	 *
	 * @param client        Index of the client.
	 * @param kv            KeyValues handle to set the menu keys and options. (Check iserverplugin.h for more information).
	 * @param type          Message type to display ingame.
	 * @error               Invalid client index, or client not connected.
	 */
	static void CreateDialog(int client, Handle kv, DialogType type)
	{
		ExecFunc(s_CreateDialogFunc, client, kv, type);
	}

	/**
	 * @brief Gets the engine version that the currently-loaded SM core was compiled against.
	 *
	 * The engine version values are not guaranteed to be in any particular order,
	 * and should only be compared by (in)equality.
	 *
	 * @return              An EngineVersion value.
	 */
	static EngineVersion GetEngineVersion()
	{
		return static_cast<EngineVersion>(ExecFunc(s_GetEngineVersionFunc));
	}

	/**
	 * @brief Prints a message to a specific client in the chat area.
	 *
	 * @param client        Client index.
	 * @param format        Formatting rules.
	 * @param ...           Variable number of format parameters.
	 * @error               If the client is not connected an error will be thrown.
	 */
	template<typename ... Args>
	static void PrintToChat(int client, const char* format, Args ... args)
	{
		PushArg(s_PrintToChatFunc, client);
		PushArg(s_PrintToChatFunc, format);
		PrintToChatSub(args...);
	}
private:
	static void PrintToChatSub()
	{
		ExecFunc(s_PrintToChatFunc);
	}

	template<typename T, typename ... Args>
	static void PrintToChatSub(T arg, Args ... args)
	{
		PushArgRef(s_PrintToChatFunc, arg);
		PrintToChatSub(args...);
	}
public:
	/**
	 * @brief Prints a message to all clients in the chat area.
	 *
	 * @param format        Formatting rules.
	 * @param ...           Variable number of format parameters.
	 */
	template<typename ... Args>
	static void PrintToChatAll(const char* format, Args ... args)
	{
		for (int i = 1; i <= s_MaxClients; i++)
		{
			if (IsClientInGame(i))
			{
				SetGlobalTransTarget(i);
				PrintToChat(i, format, args...);
			}
		}
	}

	/**
	 * @brief Prints a message to a specific client in the center of the screen.
	 *
	 * @param client        Client index.
	 * @param format        Formatting rules.
	 * @param ...           Variable number of format parameters.
	 * @error               If the client is not connected an error will be thrown.
	 */
	template<typename ... Args>
	static void PrintCenterText(int client, const char* format, Args ... args)
	{
		PushArg(s_PrintCenterTextFunc, client);
		PushArg(s_PrintCenterTextFunc, format);
		PrintCenterTextSub(args...);
	}
private:
	static void PrintCenterTextSub()
	{
		ExecFunc(s_PrintCenterTextFunc);
	}

	template<typename T, typename ... Args>
	static void PrintCenterTextSub(T arg, Args ... args)
	{
		PushArgRef(s_PrintCenterTextFunc, arg);
		PrintCenterTextSub(args...);
	}
public:
	/**
	 * @brief Prints a message to all clients in the center of the screen.
	 *
	 * @param format        Formatting rules.
	 * @param ...           Variable number of format parameters.
	 */
	template<typename ... Args>
	static void PrintCenterTextAll(const char* format, Args ... args)
	{
		for (int i = 1; i <= s_MaxClients; ++i)
		{
			if (IsClientInGame(i))
			{
				SetGlobalTransTarget(i);
				PrintCenterText(i, format, args...);
			}
		}
	}

	/**
	 * @brief Prints a message to a specific client with a hint box.
	 *
	 * @param client        Client index.
	 * @param format        Formatting rules.
	 * @param ...           Variable number of format parameters.
	 * @error               If the client is not connected an error will be thrown.
	 */
	template<typename ... Args>
	static void PrintHintText(int client, const char* format, Args ... args)
	{
		PushArg(s_PrintHintTextFunc, client);
		PushArg(s_PrintHintTextFunc, format);
		PrintHintTextSub(args...);
	}
private:
	static void PrintHintTextSub()
	{
		ExecFunc(s_PrintHintTextFunc);
	}

	template<typename T, typename ... Args>
	static void PrintHintTextSub(T arg, Args ... args)
	{
		PushArgRef(s_PrintHintTextFunc, arg);
		PrintHintTextSub(args...);
	}
public:
	/**
	 * @brief Prints a message to all clients with a hint box.
	 *
	 * @param format        Formatting rules.
	 * @param ...           Variable number of format parameters.
	 */
	template<typename ... Args>
	static void PrintHintTextToAll(const char* format, Args ... args)
	{
		for (int i = 1; i <= s_MaxClients; ++i)
		{
			if (IsClientInGame(i))
			{
				SetGlobalTransTarget(i);
				PrintHintText(i, format, args...);
			}
		}
	}

	/**
	 * @brief Shows a VGUI panel to a specific client.
	 *
	 * @param client        Client index.
	 * @param name          Panel type name (Check viewport_panel_names.h to see a list of
	 *                      some panel names).
	 * @param Kv            KeyValues handle with all the data for the panel setup (Depends
	 *                      on the panel type and may be unused).
	 * @param show          True to show the panel, or false to remove it from the client screen.
	 * @error               If the client is not connected an error will be thrown.
	 */
	static void ShowVGUIPanel(int client, const char* name, Handle Kv = INVALID_HANDLE, bool show = true)
	{
		ExecFunc(s_ShowVGUIPanelFunc, client, name, Kv, show);
	}

	/**
	 * @brief Creates a HUD synchronization object.  This object is used to automatically assign and
	 * re-use channels for a set of messages.
	 *
	 * The HUD has a hardcoded number of channels (usually 6) for displaying
	 * text.  You can use any channel for any area of the screen.  Text on
	 * different channels can overlap, but text on the same channel will
	 * erase the old text first.  This overlapping and overwriting gets problematic.
	 *
	 * A HUD synchronization object automatically selects channels for you based on
	 * the following heuristics:
	 *  - If channel X was last used by the object, and hasn't been modified again,
	 *    channel X gets re-used.
	 *  - Otherwise, a new channel is chosen based on the least-recently-used channel.
	 *
	 * This ensures that if you display text on a sync object, that the previous text
	 * displayed on it will always be cleared first.  This is because your new text
	 * will either overwrite the old text on the same channel, or because another
	 * channel has already erased your text.
	 *
	 * Note that messages can still overlap if they are on different synchronization
	 * objects, or they are displayed to manual channels.
	 *
	 * These are particularly useful for displaying repeating or refreshing HUD text, in
	 * addition to displaying multiple message sets in one area of the screen (for example,
	 * center-say messages that may pop up randomly that you don't want to overlap each
	 * other).
	 *
	 * @return              New HUD synchronization object.
	 *                      The Handle can be closed with CloseHandle().
	 *                      If HUD text is not supported on this mod, then
	 *                      INVALID_HANDLE is returned.
	 */
	static Handle CreateHudSynchronizer()
	{
		return ExecFunc(s_CreateHudSynchronizerFunc);
	}

	/**
	 * @brief Sets the HUD parameters for drawing text.  These parameters are stored
	 * globally, although nothing other than this function and SetHudTextParamsEx
	 * modify them.
	 *
	 * You must call this function before drawing text.  If you are drawing
	 * text to multiple clients, you can set the parameters once, since
	 * they won't be modified.  However, as soon as you pass control back
	 * to other plugins, you must reset the parameters next time you draw.
	 *
	 * @param x             x coordinate, from 0 to 1.  -1.0 is the center.
	 * @param y             y coordinate, from 0 to 1.  -1.0 is the center.
	 * @param holdTime      Number of seconds to hold the text.
	 * @param r             Red color value.
	 * @param g             Green color value.
	 * @param b             Blue color value.
	 * @param a             Alpha transparency value.
	 * @param effect        0/1 causes the text to fade in and fade out.
	 *                      2 causes the text to flash[?].
	 * @param fxTime        Duration of chosen effect (may not apply to all effects).
	 * @param fadeIn        Number of seconds to spend fading in.
	 * @param fadeOut       Number of seconds to spend fading out.
	 */
	static void SetHudTextParams(float x, float y, float holdTime, int r, int g, int b, int a, int effect = 0,
		float fxTime = 6.0, float fadeIn = 0.1, float fadeOut = 0.2)
	{
		ExecFunc(s_SetHudTextParamsFunc, x, y, holdTime, r, g, b, a, effect, fxTime, fadeIn, fadeOut);
	}

	/**
	 * @brief Sets the HUD parameters for drawing text.  These parameters are stored
	 * globally, although nothing other than this function and SetHudTextParams
	 * modify them.
	 *
	 * This is the same as SetHudTextParams(), except it lets you set the alternate
	 * color for when effects require it.
	 *
	 * @param x             x coordinate, from 0 to 1.  -1.0 is the center.
	 * @param y             y coordinate, from 0 to 1.  -1.0 is the center.
	 * @param holdTime      Number of seconds to hold the text.
	 * @param color1        First color set, array values being [red, green, blue, alpha]
	 * @param color2        Second color set, array values being [red, green, blue, alpha]
	 * @param effect        0/1 causes the text to fade in and fade out.
	 *                      2 causes the text to flash[?].
	 * @param fxTime        Duration of chosen effect (may not apply to all effects).
	 * @param fadeIn        Number of seconds to spend fading in.
	 * @param fadeOut       Number of seconds to spend fading out.
	 */
	static void SetHudTextParamsEx(float x, float y, float holdTime, int color1[4],
		int color2[4] = NOALPHA_COLOR, int effect = 0, float fxTime = 6.0,
		float fadeIn = 0.1, float fadeOut = 0.2)
	{
		PushArg(s_SetHudTextParamsFunc, x);
		PushArg(s_SetHudTextParamsFunc, y);
		PushArg(s_SetHudTextParamsFunc, holdTime);
		PushArg(s_SetHudTextParamsFunc, color1, 4);
		PushArg(s_SetHudTextParamsFunc, color2, 4);
		PushArg(s_SetHudTextParamsFunc, effect);
		PushArg(s_SetHudTextParamsFunc, fxTime);
		PushArg(s_SetHudTextParamsFunc, fadeIn);
		PushArg(s_SetHudTextParamsFunc, fadeOut);
		ExecFunc(s_SetHudTextParamsFunc);
	}

	/**
	 * @brief Shows a synchronized HUD message to a client.
	 *
	 * As of this writing, only TF, HL2MP, and SourceForts support HUD Text.
	 *
	 * @param client        Client index to send the message to.
	 * @param sync          Synchronization object.
	 * @param message       Message text or formatting rules.
	 * @param ...           Message formatting parameters.
	 * @return              -1 on failure, anything else on success.
	 *                      This function fails if the mod does not support it.
	 * @error               Client not in-game, or sync object not valid.
	 */
	template<typename ... Args>
	static int ShowSyncHudText(int client, Handle sync, const char* message, Args ... args)
	{
		PushArg(s_ShowSyncHudTextFunc, client);
		PushArg(s_ShowSyncHudTextFunc, sync);
		PushArg(s_ShowSyncHudTextFunc, message);
		return ShowSyncHudTextSub(args...);
	}
private:
	static int ShowSyncHudTextSub()
	{
		return ExecFunc(s_ShowSyncHudTextFunc);
	}

	template<typename T, typename ... Args>
	static int ShowSyncHudTextSub(T arg, Args ... args)
	{
		PushArgRef(s_ShowSyncHudTextFunc, arg);
		return ShowSyncHudTextSub(args...);
	}
public:
	/**
	 * @brief Clears the text on a synchronized HUD channel.
	 *
	 * This is not the same as sending "" because it guarantees that it won't
	 * overwrite text on another channel.  For example, consider the scenario:
	 *
	 * 1. Your synchronized message goes to channel 3.
	 * 2. Someone else's non-synchronized message goes to channel 3.
	 *
	 * If you were to simply send "" on your synchronized message,
	 * then someone else's text could be overwritten.
	 *
	 * @param client        Client index to send the message to.
	 * @param sync          Synchronization object.
	 * @error               Client not in-game, or sync object not valid.
	 */
	static void ClearSyncHud(int client, Handle sync)
	{
		ExecFunc(s_ClearSyncHudFunc, client, sync);
	}

	/**
	 * @brief Shows a HUD message to a client on the given channel.
	 *
	 * As of this writing, only TF, HL2MP, and SourceForts support HUD Text.
	 *
	 * @param client        Client index to send the message to.
	 * @param channel       A channel number.
	 *                      If -1, then a channel will automatically be selected
	 *                      based on the least-recently-used channel.  If the
	 *                      channel is any other number, it will be modulo'd with
	 *                      the channel count to get a final channel number.
	 * @param message       Message text or formatting rules.
	 * @param ...           Message formatting parameters.
	 * @return              -1 on failure (lack of mod support).
	 *                      Any other return value is the channel number that was
	 *                      used to render the text.
	 */
	template<typename ... Args>
	static int ShowHudText(int client, int channel, const char* message, Args ... args)
	{
		PushArg(s_ShowHudTextFunc, client);
		PushArg(s_ShowHudTextFunc, channel);
		PushArg(s_ShowHudTextFunc, message);
		return ShowHudTextSub(args...);
	}
private:
	static int ShowHudTextSub()
	{
		return ExecFunc(s_ShowHudTextFunc);
	}

	template<typename T, typename ... Args>
	static int ShowHudTextSub(T arg, Args ... args)
	{
		PushArgRef(s_ShowHudTextFunc, arg);
		return ShowHudTextSub(args...);
	}
public:
	/**
	 * @brief Shows a MOTD panel to a specific client.
	 *
	 * @param client        Client index.
	 * @param title         Title of the panel (printed on the top border of the window).
	 * @param msg           Contents of the panel, it can be treated as an url, filename or plain text
	 *                      depending on the type parameter (WARNING: msg has to be 192 bytes maximum!)
	 * @param type          Determines the way to treat the message body of the panel.
	 * @error               If the client is not connected an error will be thrown.
	 */
	static void ShowMOTDPanel(int client, const char* title, const char* msg, int type = MOTDPANEL_TYPE_INDEX)
	{
		// TODO: Finish
		/*char num[3];
		IntToString(type, num, sizeof(num));

		KeyValues kv = new KeyValues("data");
		kv.SetString("title", title);
		kv.SetString("type", num);
		kv.SetString("msg", msg);
		ShowVGUIPanel(client, "info", kv);
		delete kv;*/
	}

	/**
	 * @brief Displays a panel asking the client to connect to a specified IP.
	 *
	 * @param client        Client index.
	 * @param time          Duration to hold the panel on the client's screen.
	 * @param ip            Destination IP.
	 * @param password      Password to connect to the destination IP. The client will be able to see this.
	 */
	static void DisplayAskConnectBox(int client, float time, const char* ip, const char* password = "")
	{
		// TODO: Finish
		/*char destination[288];
		FormatEx(destination, sizeof(destination), "%s/%s", ip, password);

		KeyValues kv = new KeyValues("data");
		kv.SetFloat("time", time);
		kv.SetString("title", destination);
		CreateDialog(client, kv, DialogType_AskConnect);
		delete kv;*/
	}

	/**
	 * @brief Converts an entity index into a serial encoded entity reference.
	 *
	 * @param entity        Entity index.
	 * @return              Entity reference.
	 */
	static int EntIndexToEntRef(int entity)
	{
		return ExecFunc(s_EntIndexToEntRefFunc, entity);
	}

	/**
	 * @brief Retrieves the entity index from a reference.
	 *
	 * @param entref        Entity reference.
	 * @return              Entity index.
	 */
	static int EntRefToEntIndex(int entref)
	{
		return ExecFunc(s_EntRefToEntIndexFunc, entref);
	}

	/**
	 * @brief Converts a reference into a backwards compatible version.
	 *
	 * @param entref        Entity reference.
	 * @return              Bcompat reference.
	 */
	static int MakeCompatEntRef(int entref)
	{
		return ExecFunc(s_MakeCompatEntRefFunc, entref);
	}

	/**
	 * @brief Find clients that are potentially in range of a position.
	 *
	 * @param origin        Coordinates from which to test range.
	 * @param rangeType     Range type to use for filtering clients.
	 * @param clients       Array to which found client indexes will be written.
	 * @param size          Maximum size of clients array.
	 * @return              Number of client indexes written to clients array.
	 */
	static int GetClientsInRange(float origin[3], ClientRangeType rangeType, int* clients, int size)
	{
		PushArg(s_GetClientsInRangeFunc, origin, 3);
		PushArg(s_GetClientsInRangeFunc, rangeType);
		PushArg(s_GetClientsInRangeFunc, clients, size);
		PushArg(s_GetClientsInRangeFunc, size);
		return ExecFunc(s_GetClientsInRangeFunc);
	}

	/**
	 * @brief Retrieves the server's authentication string (SteamID).
	 *
	 * Note: If called before server is connected to Steam, auth id
	 * will be invalid ([I:0:1], 1, etc.)
	 *
	 * @param authType      Auth id type and format to use.
	 *                      (Only AuthId_Steam3 and AuthId_SteamID64 are supported)
	 * @param auth          Buffer to store the server's auth id.
	 * @param maxlen        Maximum length of string buffer (includes NULL terminator).
	 * @error               Invalid AuthIdType given.
	 */
	static void GetServerAuthId(AuthIdType authType, char* auth, int maxlen)
	{
		PushArg(s_GetServerAuthIdFunc, authType);
		PushArg(s_GetServerAuthIdFunc, auth, maxlen);
		PushArg(s_GetServerAuthIdFunc, maxlen);
		ExecFunc(s_GetServerAuthIdFunc);
	}

	/**
	 * @brief Returns the server's Steam account ID.
	 *
	 * @return              Steam account ID or 0 if not available.
	 */
	static int GetServerSteamAccountId()
	{
		return ExecFunc(s_GetServerSteamAccountIdFunc);
	}
