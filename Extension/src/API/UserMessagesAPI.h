public:
	/**
	 * Returns usermessage serialization type used for the current engine
	 *
	 * @return              The supported usermessage type.
	 */
	static UserMessageType GetUserMessageType()
	{
		return static_cast<UserMessageType>(ExecFunc(s_GetUserMessageTypeFunc));
	}

	static ProtobufHandle UserMessageToProtobuf(Handle msg)
	{
		if (GetUserMessageType() != UserMessageType::UM_Protobuf)
			return INVALID_HANDLE;
		return static_cast<ProtobufHandle>(msg);
	}

	// Make sure to only call this on writable buffers (eg from StartMessage).
	static BfWriteHandle UserMessageToBfWrite(Handle msg)
	{
		if (GetUserMessageType() == UserMessageType::UM_Protobuf)
			return INVALID_HANDLE;
		return static_cast<BfWriteHandle>(msg);
	}

	// Make sure to only call this on readable buffers (eg from a message hook).
	static BfReadHandle UserMessageToBfRead(Handle msg)
	{
		if (GetUserMessageType() == UserMessageType::UM_Protobuf)
			return INVALID_HANDLE;
		return static_cast<BfReadHandle>(msg);
	}

	/**
	 * Returns the ID of a given message, or -1 on failure.
	 *
	 * @param msg           String containing message name (case sensitive).
	 * @return              A message index, or INVALID_MESSAGE_ID on failure.
	 */
	static UserMsg GetUserMessageId(const char* msg)
	{
		return ExecFunc(s_GetUserMessageIdFunc, msg);
	}

	/**
	 * Retrieves the name of a message by ID.
	 *
	 * @param msgID         Message index.
	 * @param msg           Buffer to store the name of the message.
	 * @param maxlength     Maximum length of string buffer.
	 * @return              True if message index is valid, false otherwise.
	 */
	static bool GetUserMessageName(UserMsg msgID, char* msg, int maxlength)
	{
		PushArg(s_GetUserMessageNameFunc, msgID);
		PushArg(s_GetUserMessageNameFunc, msg, maxlength);
		PushArg(s_GetUserMessageNameFunc, maxlength);
		return ExecFunc(s_GetUserMessageNameFunc);
	}

	/**
	 * Starts a usermessage (network message).
	 *
	 * @note Only one message can be active at a time.
	 * @note It is illegal to send any message while a non-intercept hook is in progress.
	 *
	 * @param msgname       Message name to start.
	 * @param clients       Array containing player indexes to broadcast to.
	 * @param numClients    Number of players in the array.
	 * @param flags         Optional flags to set.
	 * @return              A handle to a bf_write bit packing structure, or
	 *                      INVALID_HANDLE on failure.
	 * @error               Invalid message name, unable to start a message, invalid client,
	 *                      or client not connected.
	 */
	static Handle StartMessage(const char* msgname, const int clients[], int numClients, int flags = 0)
	{
		PushArg(s_StartMessageFunc, msgname);
		PushArg(s_StartMessageFunc, clients, numClients);
		PushArg(s_StartMessageFunc, numClients);
		PushArg(s_StartMessageFunc, flags);
		return ExecFunc(s_StartMessageFunc);
	}

	/**
	 * Starts a usermessage (network message).
	 *
	 * @note Only one message can be active at a time.
	 * @note It is illegal to send any message while a non-intercept hook is in progress.
	 *
	 * @param msg           Message index to start.
	 * @param clients       Array containing player indexes to broadcast to.
	 * @param numClients    Number of players in the array.
	 * @param flags         Optional flags to set.
	 * @return              A handle to a bf_write bit packing structure, or
	 *                      INVALID_HANDLE on failure.
	 * @error               Invalid message name, unable to start a message, invalid client,
	 *                      or client not connected.
	 */
	static Handle StartMessageEx(UserMsg msg, const int clients[], int numClients, int flags = 0)
	{
		PushArg(s_StartMessageExFunc, msg);
		PushArg(s_StartMessageExFunc, clients, numClients);
		PushArg(s_StartMessageExFunc, numClients);
		PushArg(s_StartMessageExFunc, flags);
		return ExecFunc(s_StartMessageExFunc);
	}

	/**
	 * Ends a previously started user message (network message).
	 */
	static void EndMessage()
	{
		ExecFunc(s_EndMessageFunc);
	}

	/**
	 * Hooks a user message.
	 *
	 * @param msgID         Message index.
	 * @param hook          Function to use as a hook.
	 * @param intercept     If intercept is true, message will be fully intercepted,
	 *                      allowing the user to block the message.  Otherwise,
	 *                      the hook is normal and ignores the return value.
	 * @param post          Notification function.
	 * @error               Invalid message index.
	 */
	static void HookUserMessage(UserMsg msgID, MsgHookFunc hook, bool intercept = false, MsgPostHookFunc post = nullptr)
	{
		s_MsgHookCallbacks[msgID] = hook;
		s_MsgPostHookCallbacks[msgID] = post;
		ExecFunc(s_HookUserMessageFunc, msgID, intercept);
	}

	/**
	 * Removes one usermessage hook.
	 *
	 * @param msgID         Message index.
	 * @param intercept     Specifies whether the hook was an intercept hook or not.
	 * @error               Invalid message index.
	 */
	static void UnhookUserMessage(UserMsg msgID, bool intercept = false)
	{
		ExecFunc(s_UnhookUserMessageFunc, msgID, intercept);
	}

	/**
	 * Starts a usermessage (network message) that broadcasts to all clients.
	 *
	 * @note See StartMessage or StartMessageEx().
	 *
	 * @param msgname       Message name to start.
	 * @param flags         Optional flags to set.
	 * @return              A handle to a bf_write bit packing structure, or
	 *                      INVALID_HANDLE on failure.
	 */
	static Handle StartMessageAll(const char* msgname, int flags = 0)
	{
		int total = 0;
		int* clients = new int[s_MaxClients];
		for (int i = 1; i <= s_MaxClients; i++)
		{
			if (IsClientConnected(i))
			{
				clients[total++] = i;
			}
		}

		Handle res = StartMessage(msgname, clients, total, flags);
		delete[] clients;
		return res;
	}

	/**
	 * Starts a simpler usermessage (network message) for one client.
	 *
	 * @note See StartMessage or StartMessageEx().
	 *
	 * @param msgname       Message name to start.
	 * @param client        Client to send to.
	 * @param flags         Optional flags to set.
	 * @return              A handle to a bf_write bit packing structure, or
	 *                      INVALID_HANDLE on failure.
	 */
	static Handle StartMessageOne(const char* msgname, int client, int flags = 0)
	{
		int players[1];
		players[0] = client;
		return StartMessage(msgname, players, 1, flags);
	}
