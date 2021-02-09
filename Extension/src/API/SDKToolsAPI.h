public:
	/**
	 * @brief Starts the preparation of an SDK call.
	 *
	 * @param type          Type of function call this will be.
	 */
	static void StartPrepSDKCall(SDKCallType type)
	{
		ExecFunc(s_StartPrepSDKCallFunc, type);
	}

	/**
	 * @brief Sets the virtual index of the SDK call if it is virtual.
	 *
	 * @param vtblidx       Virtual table index.
	 */
	static void PrepSDKCall_SetVirtual(int vtblidx)
	{
		ExecFunc(s_PrepSDKCall_SetVirtualFunc, vtblidx);
	}

	/**
	 * @brief Finds an address in a library and sets it as the address to use for the SDK call.
	 *
	 * @param lib           Library to use.
	 * @param signature     Binary data to search for in the library.  If it starts with '@',
	 *                      the bytes parameter is ignored and the signature is interpreted
	 *                      as a symbol lookup in the library.
	 * @param bytes         Number of bytes in the binary search string.
	 * @return              True on success, false if nothing was found.
	 */
	static bool PrepSDKCall_SetSignature(SDKLibrary lib, const char* signature, int bytes)
	{
		return ExecFunc(s_PrepSDKCall_SetSignatureFunc, lib, signature, bytes);
	}

	/**
	 * @brief Uses the given function address for the SDK call.
	 *
	 * @param addr          Address of function to use.
	 * @return              True on success, false on failure.
	 */
	static bool PrepSDKCall_SetAddress(Address addr)
	{
		return ExecFunc(s_PrepSDKCall_SetAddressFunc, addr);
	}

	/**
	 * @brief Finds an address or virtual function index in a GameConfig file and sets it as
	 * the calling information for the SDK call.
	 *
	 * @param gameconf      GameConfig Handle, or INVALID_HANDLE to use sdktools.games.txt.
	 * @param source        Whether to look in Offsets or Signatures.
	 * @param name          Name of the property to find.
	 * @return              True on success, false if nothing was found.
	 */
	static bool PrepSDKCall_SetFromConf(Handle gameconf, SDKFuncConfSource source, const char* name)
	{
		return ExecFunc(s_PrepSDKCall_SetFromConfFunc, gameconf, source, name);
	}

	/**
	 * @brief Sets the return information of an SDK call.  Do not call this if there is no return data.
	 * This must be called if there is a return value (i.e. it is not necessarily safe to ignore
	 * the data).
	 *
	 * @param type          Data type to convert to/from.
	 * @param pass          How the data is passed in C++.
	 * @param decflags      Flags on decoding from the plugin to C++.
	 * @param encflags      Flags on encoding from C++ to the plugin.
	 */
	static void PrepSDKCall_SetReturnInfo(SDKType type, SDKPassMethod pass, int decflags = 0, int encflags = 0)
	{
		ExecFunc(s_PrepSDKCall_SetReturnInfoFunc, type, pass, decflags, encflags);
	}

	/**
	 * @brief Adds a parameter to the calling convention.  This should be called in normal ascending order.
	 *
	 * @param type          Data type to convert to/from.
	 * @param pass          How the data is passed in C++.
	 * @param decflags      Flags on decoding from the plugin to C++.
	 * @param encflags      Flags on encoding from C++ to the plugin.
	 */
	static void PrepSDKCall_AddParameter(SDKType type, SDKPassMethod pass, int decflags = 0, int encflags = 0)
	{
		ExecFunc(s_PrepSDKCall_AddParameterFunc, type, pass, decflags, encflags);
	}

	/**
	 * Finalizes an SDK call preparation and returns the resultant Handle.
	 *
	 * @return              A new SDKCall Handle on success, or INVALID_HANDLE on failure.
	 */
	static Handle EndPrepSDKCall()
	{
		return ExecFunc(s_EndPrepSDKCallFunc);
	}

	/**
	 * @brief Calls an SDK function with the given parameters.
	 *
	 * If the call type is Entity or Player, the index MUST ALWAYS be the FIRST parameter passed.
	 * If the call type is GameRules, then nothing special needs to be passed.
	 * If the return value is a Vector or QAngles, the SECOND parameter must be a Float[3].
	 * If the return value is a string, the THIRD parameter must be a String buffer, and the
	 *  FOURTH parameter must be the maximum length.
	 * All parameters must be passed after the above is followed.  Failure to follow these
	 *  rules will result in crashes or wildly unexpected behavior!
	 *
	 * If the return value is a float or integer, the return value will be this value.
	 * If the return value is a CBaseEntity, CBasePlayer, or edict, the return value will
	 *  always be the entity index, or -1 for NULL.
	 *
	 * @param call          SDKCall Handle.
	 * @param args          Call Parameters.
	 * @return              Simple return value, if any (up to 10)
	 * @error               Invalid Handle or internal decoding error.
	 */
	template<typename T, typename ... Args>
	static T SDKCall(Handle call, Args ... args)
	{
		int count = SDKCallDetermineSize(args...);

		auto GetSDKCallFunc = [](int count) -> IPluginFunction*
		{
			switch (count)
			{
				case 0: return s_SDKCall0Func; break;
				case 1: return s_SDKCall1Func; break;
				case 2: return s_SDKCall2Func; break;
				case 3: return s_SDKCall3Func; break;
				case 4: return s_SDKCall4Func; break;
				case 5: return s_SDKCall5Func; break;
				case 6: return s_SDKCall6Func; break;
				case 7: return s_SDKCall7Func; break;
				case 8: return s_SDKCall8Func; break;
				case 9: return s_SDKCall9Func; break;
				case 10: return s_SDKCall10Func; break;
			}

			return nullptr;
		};

		IPluginFunction* func = GetSDKCallFunc(count);
		if (func == nullptr)
		{
			PrintToServer("Could not find appropriate SDKCall function for %d arguments!", count);
			return static_cast<T>(0);
		}

		PushArg(func, call);
		return SDKCallSub<T>(func, args...);
	}
private:
	template<typename T>
	static T SDKCallSub(IPluginFunction* func)
	{
		return static_cast<T>(ExecFunc(func));
	}

	template<typename T, typename T1, typename ... Args>
	static T SDKCallSub(IPluginFunction* func, T1 arg, Args ... args)
	{
		PushArg(func, arg);
		return SDKCallSub<T>(func, args...);
	}

	static int SDKCallDetermineSize()
	{
		return 0;
	}

	template<typename T, typename ... Args>
	static int SDKCallDetermineSize(T, Args ... args)
	{
		return 1 + SDKCallDetermineSize(args...);
	}

	template<typename R>
	static R SDKCall0(Handle call)
	{

	}

	template<typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
	static R SDKCall10(Handle call, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9, T10 t10)
	{
		return static_cast<R>(ExecFunc(s_SDKCall0Func, call, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10));
	}
public:
	/**
	 * @brief Returns the entity index of the player resource/manager entity.
	 *
	 * @return              Index of resource entity or -1 if not found.
	 */
	static int GetPlayerResourceEntity()
	{
		return ExecFunc(s_GetPlayerResourceEntityFunc);
	}