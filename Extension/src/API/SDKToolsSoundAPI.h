public:
	/**
	 * Prefetches a sound.
	 *
	 * @param name          Sound file name relative to the "sound" folder.
	 */
	static void PrefetchSound(const char* name)
	{
		ExecFunc(s_PrefetchSoundFunc, name);
	}

	/**
	 * Emits an ambient sound.
	 *
	 * @param name          Sound file name relative to the "sound" folder.
	 * @param pos           Origin of sound.
	 * @param entity        Entity index to associate sound with.
	 * @param level         Sound level (from 0 to 255).
	 * @param flags         Sound flags.
	 * @param vol           Volume (from 0.0 to 1.0).
	 * @param pitch         Pitch (from 0 to 255).
	 * @param delay         Play delay.
	 */
	static void EmitAmbientSound(const char* name, const float pos[3], int entity = SOUND_FROM_WORLD, int level = SNDLEVEL_NORMAL,
		int flags = SND_NOFLAGS, float vol = SNDVOL_NORMAL, int pitch = SNDPITCH_NORMAL, float delay = 0.0f)
	{
		PushArg(s_EmitAmbientSoundFunc, name);
		PushArg(s_EmitAmbientSoundFunc, pos, 3);
		PushArg(s_EmitAmbientSoundFunc, entity);
		PushArg(s_EmitAmbientSoundFunc, level);
		PushArg(s_EmitAmbientSoundFunc, flags);
		PushArg(s_EmitAmbientSoundFunc, vol);
		PushArg(s_EmitAmbientSoundFunc, pitch);
		PushArg(s_EmitAmbientSoundFunc, delay);
		ExecFunc(s_EmitAmbientSoundFunc);
	}

	/**
	 * Fades a client's volume level toward silence or a given percentage.
	 *
	 * @param client        Client index.
	 * @param percent       Fade percentage.
	 * @param outtime       Fade out time, in seconds.
	 * @param holdtime      Hold time, in seconds.
	 * @param intime        Fade in time, in seconds.
	 * @error               Invalid client index or client not in game.
	 */
	static void FadeClientVolume(int client, float percent, float outtime, float holdtime, float intime)
	{
		ExecFunc(s_FadeClientVolumeFunc, client, percent, outtime, holdtime, intime);
	}

	/**
	 * Stops a sound.
	 *
	 * @param entity        Entity index.
	 * @param channel       Channel number.
	 * @param name          Sound file name relative to the "sound" folder.
	 */
	static void StopSound(int entity, int channel, const char* name)
	{
		ExecFunc(s_StopSoundFunc, entity, channel, name);
	}

	/**
	 * Emits a sound to a list of clients.
	 *
	 * @param clients       Array of client indexes.
	 * @param numClients    Number of clients in the array.
	 * @param sample        Sound file name relative to the "sound" folder.
	 * @param entity        Entity to emit from.
	 * @param channel       Channel to emit with.
	 * @param level         Sound level.
	 * @param flags         Sound flags.
	 * @param volume        Sound volume.
	 * @param pitch         Sound pitch.
	 * @param speakerentity Unknown.
	 * @param origin        Sound origin.
	 * @param dir           Sound direction.
	 * @param updatePos     Unknown (updates positions?)
	 * @param soundtime     Alternate time to play sound for.
	 * @param ...           Optional list of Float[3] arrays to specify additional origins.
	 * @error               Invalid client index.
	 */
	static void EmitSound(const int clients[], int numClients, const char* sample, int entity = SOUND_FROM_PLAYER,
		int channel = SNDCHAN_AUTO, int level = SNDLEVEL_NORMAL, int flags = SND_NOFLAGS, float volume = SNDVOL_NORMAL,
		int pitch = SNDPITCH_NORMAL, int speakerentity = -1, const float origin[3] = nullptr, const float dir[3] = nullptr,
		bool updatePos = true, float soundtime = 0.0f)
	{
		PushArg(s_EmitSoundFunc, clients, numClients);
		PushArg(s_EmitSoundFunc, numClients);
		PushArg(s_EmitSoundFunc, sample);
		PushArg(s_EmitSoundFunc, entity);
		PushArg(s_EmitSoundFunc, channel);
		PushArg(s_EmitSoundFunc, level);
		PushArg(s_EmitSoundFunc, flags);
		PushArg(s_EmitSoundFunc, volume);
		PushArg(s_EmitSoundFunc, pitch);
		PushArg(s_EmitSoundFunc, speakerentity);
		if (origin == nullptr)
			PushArg(s_EmitSoundFunc, NULL_VECTOR);
		else
			PushArg(s_EmitSoundFunc, origin, 3);

		if (dir == nullptr)
			PushArg(s_EmitSoundFunc, NULL_VECTOR);
		else
			PushArg(s_EmitSoundFunc, dir, 3);

		PushArg(s_EmitSoundFunc, updatePos);
		PushArg(s_EmitSoundFunc, soundtime);
		ExecFunc(s_EmitSoundFunc);
	}

	/**
	 * Emits a sound or game sound to a list of clients using the latest version of the engine sound interface.
	 * This native is only available in engines that are greater than or equal to Portal 2.
	 *
	 * @param clients       Array of client indexes.
	 * @param numClients    Number of clients in the array.
	 * @param soundEntry    Sound entry name.
	 * @param sample        Sound file name relative to the "sound" folder.
	 * @param entity        Entity to emit from.
	 * @param channel       Channel to emit with.
	 * @param level         Sound level.
	 * @param seed          Sound seed.
	 * @param flags         Sound flags.
	 * @param volume        Sound volume.
	 * @param pitch         Sound pitch.
	 * @param speakerentity Unknown.
	 * @param origin        Sound origin.
	 * @param dir           Sound direction.
	 * @param updatePos     Unknown (updates positions?)
	 * @param soundtime     Alternate time to play sound for.
	 * @param ...           Optional list of Float[3] arrays to specify additional origins.
	 * @error               Invalid client index.
	 */
	static void EmitSoundEntry(const int clients[], int numClients, const char* soundEntry, const char* sample, int entity = SOUND_FROM_PLAYER,
		int channel = SNDCHAN_AUTO, int level = SNDLEVEL_NORMAL, int seed = 0, int flags = SND_NOFLAGS, float volume = SNDVOL_NORMAL,
		int pitch = SNDPITCH_NORMAL, int speakerentity = -1, const float origin[3] = nullptr, const float dir[3] = nullptr,
		bool updatePos = true, float soundtime = 0.0f)
	{
		PushArg(s_EmitSoundEntryFunc, clients, numClients);
		PushArg(s_EmitSoundEntryFunc, numClients);
		PushArg(s_EmitSoundEntryFunc, soundEntry);
		PushArg(s_EmitSoundEntryFunc, sample);
		PushArg(s_EmitSoundEntryFunc, entity);
		PushArg(s_EmitSoundEntryFunc, channel);
		PushArg(s_EmitSoundEntryFunc, level);
		PushArg(s_EmitSoundEntryFunc, seed);
		PushArg(s_EmitSoundEntryFunc, flags);
		PushArg(s_EmitSoundEntryFunc, volume);
		PushArg(s_EmitSoundEntryFunc, pitch);
		PushArg(s_EmitSoundEntryFunc, speakerentity);
		if (origin == nullptr)
			PushArg(s_EmitSoundEntryFunc, NULL_VECTOR);
		else
			PushArg(s_EmitSoundEntryFunc, origin, 3);

		if (dir == nullptr)
			PushArg(s_EmitSoundEntryFunc, NULL_VECTOR);
		else
			PushArg(s_EmitSoundEntryFunc, dir, 3);

		PushArg(s_EmitSoundEntryFunc, updatePos);
		PushArg(s_EmitSoundEntryFunc, soundtime);
		ExecFunc(s_EmitSoundEntryFunc);
	}

	/**
	 * Emits a sentence to a list of clients.
	 *
	 * @param clients       Array of client indexes.
	 * @param numClients    Number of clients in the array.
	 * @param sentence      Sentence index (from PrecacheSentenceFile).
	 * @param entity        Entity to emit from.
	 * @param channel       Channel to emit with.
	 * @param level         Sound level.
	 * @param flags         Sound flags.
	 * @param volume        Sound volume.
	 * @param pitch         Sound pitch.
	 * @param speakerentity Unknown.
	 * @param origin        Sound origin.
	 * @param dir           Sound direction.
	 * @param updatePos     Unknown (updates positions?)
	 * @param soundtime     Alternate time to play sound for.
	 * @param ...           Optional list of Float[3] arrays to specify additional origins.
	 * @error               Invalid client index.
	 */
	static void EmitSentence(const int clients[], int numClients, int sentence, int entity, int channel = SNDCHAN_AUTO,
		int level = SNDLEVEL_NORMAL, int flags = SND_NOFLAGS, float volume = SNDVOL_NORMAL, int pitch = SNDPITCH_NORMAL,
		int speakerentity = -1, const float origin[3] = nullptr, const float dir[3] = nullptr, bool updatePos = true,
		float soundtime = 0.0f)
	{
		PushArg(s_EmitSentenceFunc, clients, numClients);
		PushArg(s_EmitSentenceFunc, numClients);
		PushArg(s_EmitSentenceFunc, sentence);
		PushArg(s_EmitSentenceFunc, entity);
		PushArg(s_EmitSentenceFunc, channel);
		PushArg(s_EmitSentenceFunc, level);
		PushArg(s_EmitSentenceFunc, flags);
		PushArg(s_EmitSentenceFunc, volume);
		PushArg(s_EmitSentenceFunc, pitch);
		PushArg(s_EmitSentenceFunc, speakerentity);
		if (origin == nullptr)
			PushArg(s_EmitSentenceFunc, NULL_VECTOR);
		else
			PushArg(s_EmitSentenceFunc, origin, 3);

		if (dir == nullptr)
			PushArg(s_EmitSentenceFunc, NULL_VECTOR);
		else
			PushArg(s_EmitSentenceFunc, dir, 3);

		PushArg(s_EmitSentenceFunc, updatePos);
		PushArg(s_EmitSentenceFunc, soundtime);
		ExecFunc(s_EmitSentenceFunc);
	}

	/**
	 * Calculates gain of sound on given distance with given sound level in decibel
	 *
	 * @param soundlevel    decibel of sound, like SNDLEVEL_NORMAL or integer value
	 * @param distance      distance of sound to calculate, not meter or feet, but Source Engine`s normal Coordinate unit
	 * @return              gain of sound. you can multiply this with original sound`s volume to calculate volume on given distance
	 */
	static float GetDistGainFromSoundLevel(int soundlevel, float distance)
	{
		return ExecFunc(s_GetDistGainFromSoundLevelFunc, soundlevel, distance);
	}

	/**
	 * Hooks all played ambient sounds.
	 *
	 * @param hook          Function to use as a hook.
	 * @error               Invalid function hook.
	 */
	static void AddAmbientSoundHook(AmbientSHookFunc hook)
	{
		s_AmbientSHookCallback = hook;
		ExecFunc(s_AddAmbientSoundHookFunc);
	}

	/**
	 * Hooks all played normal sounds.
	 *
	 * @param hook          Function to use as a hook.
	 * @error               Invalid function hook.
	 */
	static void AddNormalSoundHook(NormalSHookFunc hook)
	{
		s_NormalSHookCallback = hook;
		ExecFunc(s_AddNormalSoundHookFunc);
	}

	/**
	 * Unhooks all played ambient sounds.
	 *
	 * @error               Invalid function hook.
	 */
	static void RemoveAmbientSoundHook()
	{
		ExecFunc(s_RemoveAmbientSoundHookFunc);
	}

	/**
	 * Unhooks all played normal sounds.
	 *
	 * @error               Invalid function hook.
	 */
	static void RemoveNormalSoundHook()
	{
		ExecFunc(s_RemoveNormalSoundHookFunc);
	}

	/**
	 * Wrapper to emit sound to one client.
	 *
	 * @param client        Client index.
	 * @param sample        Sound file name relative to the "sound" folder.
	 * @param entity        Entity to emit from.
	 * @param channel       Channel to emit with.
	 * @param level         Sound level.
	 * @param flags         Sound flags.
	 * @param volume        Sound volume.
	 * @param pitch         Sound pitch.
	 * @param speakerentity Unknown.
	 * @param origin        Sound origin.
	 * @param dir           Sound direction.
	 * @param updatePos     Unknown (updates positions?)
	 * @param soundtime     Alternate time to play sound for.
	 * @error               Invalid client index.
	 */
	static void EmitSoundToClient(int client, const char* sample, int entity = SOUND_FROM_PLAYER, int channel = SNDCHAN_AUTO,
		int level = SNDLEVEL_NORMAL, int flags = SND_NOFLAGS, float volume = SNDVOL_NORMAL, int pitch = SNDPITCH_NORMAL,
		int speakerentity = -1, const float origin[3] = nullptr, const float dir[3] = nullptr, bool updatePos = true,
		float soundtime = 0.0)
	{
		int clients[1];
		clients[0] = client;
		/* Save some work for SDKTools and remove SOUND_FROM_PLAYER references */
		entity = (entity == SOUND_FROM_PLAYER) ? client : entity;
		EmitSound(clients, 1, sample, entity, channel, level, flags, volume, pitch, speakerentity, origin, dir, updatePos, soundtime);
	}

	/**
	 * Wrapper to emit sound to all clients.
	 *
	 * @param sample        Sound file name relative to the "sound" folder.
	 * @param entity        Entity to emit from.
	 * @param channel       Channel to emit with.
	 * @param level         Sound level.
	 * @param flags         Sound flags.
	 * @param volume        Sound volume.
	 * @param pitch         Sound pitch.
	 * @param speakerentity Unknown.
	 * @param origin        Sound origin.
	 * @param dir           Sound direction.
	 * @param updatePos     Unknown (updates positions?)
	 * @param soundtime     Alternate time to play sound for.
	 * @error               Invalid client index.
	 */
	static void EmitSoundToAll(const char* sample, int entity = SOUND_FROM_PLAYER, int channel = SNDCHAN_AUTO,
		int level = SNDLEVEL_NORMAL, int flags = SND_NOFLAGS, float volume = SNDVOL_NORMAL, int pitch = SNDPITCH_NORMAL,
		int speakerentity = -1, const float origin[3] = nullptr, const float dir[3] = nullptr,
		bool updatePos = true, float soundtime = 0.0f)
	{
		int* clients = new int[s_MaxClients];
		int total = 0;
		for (int i = 1; i <= s_MaxClients; i++)
			if (IsClientInGame(i))
				clients[total++] = i;

		if (total)
			EmitSound(clients, total, sample, entity, channel, level, flags, volume, pitch, speakerentity, origin, dir, updatePos, soundtime);
		delete[] clients;
	}

	/**
	 * Converts an attenuation value to a sound level.
	 * This function is from the HL2SDK.
	 *
	 * @param attn          Attenuation value.
	 * @return              Integer sound level.
	 */
	static int ATTN_TO_SNDLEVEL(float attn)
	{
		float value = 50.0 + (20.0 / attn);
		if (attn > 0.0)
			return static_cast<int>(value + 0.5f);
		return 0;
	}

	/**
	 * Retrieves the parameters for a game sound.
	 *
	 * Game sounds are found in a game's scripts/game_sound.txt or other files
	 * referenced from it
	 *
	 * Note that if a game sound has a rndwave section, one of them will be returned
	 * at random.
	 *
	 * @param gameSound     Name of game sound.
	 * @param channel       Channel to emit with.
	 * @param level         Sound level.
	 * @param volume        Sound volume.
	 * @param pitch         Sound pitch.
	 * @param sample        Sound file name relative to the "sound" folder.
	 * @param maxlength     Maximum length of sample string buffer.
	 * @param entity        Entity the sound is being emitted from.
	 * @return              True if the sound was successfully retrieved, false if it
	 *                      was not found
	 */
	static bool GetGameSoundParams(const char* gameSound, int& channel, int& soundLevel, float& volume, int& pitch,
		char* sample, int maxlength, int entity = SOUND_FROM_PLAYER)
	{
		PushArg(s_GetGameSoundParamsFunc, gameSound);
		PushArgRef(s_GetGameSoundParamsFunc, channel);
		PushArgRef(s_GetGameSoundParamsFunc, soundLevel);
		PushArgRef(s_GetGameSoundParamsFunc, volume);
		PushArgRef(s_GetGameSoundParamsFunc, pitch);
		PushArg(s_GetGameSoundParamsFunc, sample, maxlength);
		PushArg(s_GetGameSoundParamsFunc, maxlength);
		PushArg(s_GetGameSoundParamsFunc, entity);
		return ExecFunc(s_GetGameSoundParamsFunc);
	}

	/**
	 * Emits a game sound to a list of clients.
	 *
	 * Game sounds are found in a game's scripts/game_sound.txt or other files
	 * referenced from it
	 *
	 * Note that if a game sound has a rndwave section, one of them will be returned
	 * at random.
	 *
	 * @param clients       Array of client indexes.
	 * @param numClients    Number of clients in the array.
	 * @param gameSound     Name of game sound.
	 * @param entity        Entity to emit from.
	 * @param flags         Sound flags.
	 * @param speakerentity Unknown.
	 * @param origin        Sound origin.
	 * @param dir           Sound direction.
	 * @param updatePos     Unknown (updates positions?)
	 * @param soundtime     Alternate time to play sound for.
	 * @return              True if the sound was played successfully, false if it failed
	 * @error               Invalid client index.
	 */
	static bool EmitGameSound(const int clients[], int numClients, const char* gameSound, int entity = SOUND_FROM_PLAYER,
		int flags = SND_NOFLAGS, int speakerentity = -1, const float origin[3] = nullptr, const float dir[3] = nullptr,
		bool updatePos = true, float soundtime = 0.0)
	{
		int channel, level, pitch;
		float volume;
		char sample[PLATFORM_MAX_PATH];
		if (GetGameSoundParams(gameSound, channel, level, volume, pitch, sample, sizeof(sample), entity))
		{
			EmitSound(clients, numClients, sample, entity, channel, level, flags, volume, pitch, speakerentity, origin, dir, updatePos, soundtime);
			return true;
		}

		return false;
	}

	/**
	 * Emits an ambient game sound.
	 *
	 * Game sounds are found in a game's scripts/game_sound.txt or other files
	 * referenced from it
	 *
	 * Note that if a game sound has a rndwave section, one of them will be returned
	 * at random.
	 *
	 * @param gameSound     Name of game sound.
	 * @param pos           Origin of sound.
	 * @param entity        Entity index to associate sound with.
	 * @param flags         Sound flags.
	 * @param delay         Play delay.
	 */
	static bool EmitAmbientGameSound(const char* gameSound, const float pos[3], int entity = SOUND_FROM_WORLD,
		int flags = SND_NOFLAGS, float delay = 0.0f)
	{
		int channel; // This is never actually used for Ambients, but it's a mandatory field to GetGameSoundParams
		int level, pitch;
		float volume;
		char sample[PLATFORM_MAX_PATH];
		if (GetGameSoundParams(gameSound, channel, level, volume, pitch, sample, sizeof(sample), entity))
		{
			EmitAmbientSound(sample, pos, entity, level, flags, volume, pitch, delay);
			return true;
		}

		return false;
	}

	/**
	 * Wrapper to emit a game sound to one client.
	 *
	 * Game sounds are found in a game's scripts/game_sound.txt or other files
	 * referenced from it
	 *
	 * Note that if a game sound has a rndwave section, one of them will be returned
	 * at random.
	 *
	 * @param client        Client index.
	 * @param gameSound     Name of game sound.
	 * @param entity        Entity to emit from.
	 * @param flags         Sound flags.
	 * @param speakerentity Unknown.
	 * @param origin        Sound origin.
	 * @param dir           Sound direction.
	 * @param updatePos     Unknown (updates positions?)
	 * @param soundtime     Alternate time to play sound for.
	 * @error               Invalid client index.
	 */
	static bool EmitGameSoundToClient(int client, const char* gameSound, int entity = SOUND_FROM_PLAYER, int flags = SND_NOFLAGS,
		int speakerentity = -1, const float origin[3] = nullptr, const float dir[3] = nullptr, bool updatePos = true,
		float soundtime = 0.0f)
	{
		int clients[1];
		clients[0] = client;
		/* Save some work for SDKTools and remove SOUND_FROM_PLAYER references */
		entity = (entity == SOUND_FROM_PLAYER) ? client : entity;
		return EmitGameSound(clients, 1, gameSound, entity, flags, speakerentity, origin, dir, updatePos, soundtime);
	}

	/**
	 * Wrapper to emit game sound to all clients.
	 *
	 * Game sounds are found in a game's scripts/game_sound.txt or other files
	 * referenced from it
	 *
	 * Note that if a game sound has a rndwave section, one of them will be returned
	 * at random.
	 *
	 * @param gameSound     Name of game sound.
	 * @param entity        Entity to emit from.
	 * @param flags         Sound flags.
	 * @param speakerentity Unknown.
	 * @param origin        Sound origin.
	 * @param dir           Sound direction.
	 * @param updatePos     Unknown (updates positions?)
	 * @param soundtime     Alternate time to play sound for.
	 * @error               Invalid client index.
	 */
	static bool EmitGameSoundToAll(const char* gameSound, int entity = SOUND_FROM_PLAYER, int flags = SND_NOFLAGS,
		int speakerentity = -1, const float origin[3] = nullptr, const float dir[3] = nullptr, bool updatePos = true,
		float soundtime = 0.0f)
	{
		int* clients = new int[s_MaxClients];
		int total = 0;
		for (int i = 1; i <= s_MaxClients; i++)
			if (IsClientInGame(i))
				clients[total++] = i;

		if (!total)
		{
			delete[] clients;
			return false;
		}

		bool ret = EmitGameSound(clients, total, gameSound, entity, flags, speakerentity, origin, dir, updatePos, soundtime);
		delete[] clients;
		return ret;
	}

	/**
	 * Precache a game sound.
	 *
	 * Most games will precache all game sounds on map start, but this is not guaranteed...
	 * Team Fortress 2 is known to not pre-cache MvM game mode sounds on non-MvM maps.
	 *
	 * Due to the above, this native should be called before any calls to GetGameSoundParams,
	 * EmitGameSound*, or EmitAmbientGameSound.
	 *
	 * It should be safe to pass already precached game sounds to this function.
	 *
	 * Note: It precaches all files for a game sound.
	 *
	 * @param soundname     Game sound to precache
	 * @return              True if the game sound was found, false if sound did not exist
	 *                      or had no files
	 */
	static bool PrecacheScriptSound(const char* soundname)
	{
		return ExecFunc(s_PrecacheScriptSoundFunc, soundname);
	}
