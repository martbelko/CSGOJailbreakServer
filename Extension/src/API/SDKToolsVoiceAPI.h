public:
	/**
	 * Set the client listening flags.
	 *
	 * @param client        The client index
	 * @param flags         The voice flags
	 */
	static void SetClientListeningFlags(int client, int flags)
	{
		ExecFunc(s_SetClientListeningFlagsFunc, client, flags);
	}

	/**
	 * Retrieve the client current listening flags.
	 *
	 * @param client        The client index
	 * @return              The current voice flags
	 */
	static int GetClientListeningFlags(int client)
	{
		return ExecFunc(s_GetClientListeningFlagsFunc, client);
	}

	/**
	 * Override the receiver's ability to listen to the sender.
	 *
	 * @param iReceiver     The listener index.
	 * @param iSender       The sender index.
	 * @param overRide      The override of the receiver's ability to listen to the sender.
	 * @return              True if successful otherwise false.
	 */
	static bool SetListenOverride(int iReceiver, int iSender, ListenOverride overRide)
	{
		return ExecFunc(s_SetListenOverrideFunc, iReceiver, iSender, overRide);
	}

	/**
	 * Retrieves the override of the receiver's ability to listen to the sender.
	 *
	 * @param iReceiver     The listener index.
	 * @param iSender       The sender index.
	 * @return              The override value.
	 */
	static ListenOverride GetListenOverride(int iReceiver, int iSender)
	{
		return static_cast<ListenOverride>(ExecFunc(s_GetListenOverrideFunc, iReceiver, iSender));
	}

	/**
	 * Retrieves if the muter has muted the mutee.
	 *
	 * @param iMuter        The muter index.
	 * @param iMutee        The mutee index.
	 * @return              True if muter has muted mutee, false otherwise.
	 */
	static bool IsClientMuted(int iMuter, int iMutee)
	{
		return ExecFunc(s_IsClientMutedFunc, iMuter, iMutee);
	}
