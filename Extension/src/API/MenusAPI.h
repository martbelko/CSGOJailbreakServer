public:
	/**
	 * @brief Creates a new, empty menu using the default style.
	 *
	 * @param handler       Function which will receive menu actions.
	 * @param actions       Optionally set which actions to receive.  Select,
	 *                      Cancel, and End will always be received regardless
	 *                      of whether they are set or not.  They are also
	 *                      the only default actions.
	 * @return              A new menu Handle.
	 */
	static MenuHandle CreateMenu(MenuHandler handler, MenuAction actions = MENU_ACTIONS_DEFAULT)
	{
		MenuHandle handle = ExecFunc(s_CreateMenuFunc, actions);
		s_MenuHandlers[handle] = handler;
		return handle;
	}

	/**
	 * @brief Displays a menu to a client.
	 *
	 * @param menu          Menu Handle.
	 * @param client        Client index.
	 * @param time          Maximum time to leave menu on the screen.
	 * @return              True on success, false on failure.
	 * @error               Invalid Handle or client not in game.
	 */
	static bool DisplayMenu(Handle menu, int client, int time)
	{
		return ExecFunc(s_DisplayMenuFunc, menu, client, time);
	}

	/**
	 * @brief Displays a menu to a client, starting from the given item.
	 *
	 * @param menu          Menu Handle.
	 * @param client        Client index.
	 * @param firstItem     First item to begin drawing from.
	 * @param time          Maximum time to leave menu on the screen.
	 * @return              True on success, false on failure.
	 * @error               Invalid Handle or client not in game.
	 */
	static bool DisplayMenuAtItem(Handle menu, int client, int firstItem, int time)
	{
		return ExecFunc(s_DisplayMenuAtItemFunc, menu, client, firstItem, time);
	}

	/**
	 * @brief Appends a new item to the end of a menu.
	 *
	 * @param menu          Menu Handle.
	 * @param info          Item information string.
	 * @param display       Default item display string.
	 * @param style         Drawing style flags.  Anything other than DEFAULT or
	 *                      DISABLED will be completely ignored when paginating.
	 * @return              True on success, false on failure.
	 * @error               Invalid Handle or item limit reached.
	 */
	static bool AddMenuItem(Handle menu, const char* info, const char* display, int style = ITEMDRAW_DEFAULT)
	{
		return ExecFunc(s_AddMenuItemFunc, menu, info, display, style);
	}

	/**
	* @brief Inserts an item into the menu before a certain position; the new item will
	* be at the given position and all next items pushed forward.
	*
	* @param menu          Menu Handle.
	* @param position      Position, starting from 0.
	* @param info          Item information string.
	* @param display       Default item display string.
	* @param style         Drawing style flags.  Anything other than DEFAULT or
	*                      DISABLED will be completely ignored when paginating.
	* @return              True on success, false on failure.
	* @error               Invalid Handle or menu position.
	*/
	static bool InsertMenuItem(Handle menu, int position, const char* info, const char* display, int style = ITEMDRAW_DEFAULT)
	{
		return ExecFunc(s_InsertMenuItemFunc, menu, position, info, display, style);
	}

	/**
	 * @brief Removes an item from the menu.
	 *
	 * @param menu          Menu Handle.
	 * @param position      Position, starting from 0.
	 * @return              True on success, false on failure.
	 * @error               Invalid Handle or menu position.
	 */
	static bool RemoveMenuItem(Handle menu, int position)
	{
		return ExecFunc(s_RemoveMenuItemFunc, menu, position);
	}

	/**
	 * @brief Removes all items from a menu.
	 *
	 * @param menu          Menu Handle.
	 * @error               Invalid Handle or menu position.
	 */
	static void RemoveAllMenuItems(Handle menu)
	{
		ExecFunc(s_RemoveAllMenuItemsFunc, menu);
	}

	/**
	 * @brief Retrieves information about a menu item.
	 *
	 * @param menu          Menu Handle.
	 * @param position      Position, starting from 0.
	 * @param infoBuf       Info buffer.
	 * @param infoBufLen    Maximum length of the info buffer.
	 * @param style         By-reference variable to store drawing flags.
	 * @param dispBuf       Display buffer.
	 * @param dispBufLen    Maximum length of the display buffer.
	 * @param client		Client index. Must be specified if menu is per-client random shuffled, -1 to ignore.
	 * @return              True on success, false if position is invalid.
	 * @error               Invalid Handle.
	 */
	static bool GetMenuItem(Handle menu, int position, char* infoBuf, int infoBufLen, int& style = NULL_VALUE,
		char* dispBuf = "", int dispBufLen = 0, int client = 0)
	{
		PushArg(s_GetMenuItemFunc, menu);
		PushArg(s_GetMenuItemFunc, position);
		PushArg(s_GetMenuItemFunc, infoBuf, infoBufLen);
		PushArg(s_GetMenuItemFunc, infoBufLen);
		PushArgRef(s_GetMenuItemFunc, style);
		PushArg(s_GetMenuItemFunc, dispBuf, dispBufLen);
		PushArg(s_GetMenuItemFunc, dispBufLen);
		PushArg(s_GetMenuItemFunc, client);
		return ExecFunc(s_GetMenuItemFunc);
	}

	/**
	 * @brief Generates a per-client random mapping for the current vote options.
	 *
	 * @param menu          Menu Handle.
	 * @param start         Menu item index to start randomizing from.
	 * @param stop          Menu item index to stop randomizing at. -1 = infinite
	 */
	static void MenuShufflePerClient(Handle menu, int start = 0, int stop = -1)
	{
		ExecFunc(s_MenuShufflePerClientFunc, menu, start, stop);
	}

	/*
	 * @brief Fills the client vote option mapping with user supplied values.
	 *
	 * @param menu          Menu Handle.
	 * @param client		Client index.
	 * @param array			Integer array with mapping.
	 * @param length		Length of array.
	 */
	static void MenuSetClientMapping(Handle menu, int client, int arr[], int length)
	{
		PushArg(s_MenuSetClientMappingFunc, menu);
		PushArg(s_MenuSetClientMappingFunc, client);
		PushArg(s_MenuSetClientMappingFunc, arr, length);
		PushArg(s_MenuSetClientMappingFunc, length);
		ExecFunc(s_MenuSetClientMappingFunc);
	}

	/**
	 * @brief Returns the first item on the page of a currently selected menu.
	 *
	 * This is only valid inside a MenuAction_Select callback.
	 *
	 * @return              First item number on the page the client was viewing
	 *                      before selecting the item in the callback.  This can
	 *                      be used to re-display the menu from the original
	 *                      position.
	 * @error               Not called from inside a MenuAction_Select callback.
	 */
	static int GetMenuSelectionPosition()
	{
		return ExecFunc(s_GetMenuSelectionPositionFunc);
	}

	/**
	 * @brief Returns the number of items in a menu.
	 *
	 * @param menu          Menu Handle.
	 * @return              Number of items in the menu.
	 * @error               Invalid Handle.
	 */

	static int GetMenuItemCount(Handle menu)
	{
		return ExecFunc(s_GetMenuItemCountFunc, menu);
	}
	/**
	 * @brief Sets whether the menu should be paginated or not.
	 *
	 * If itemsPerPage is MENU_NO_PAGINATION, and the exit button flag is set,
	 * then the exit button flag is removed.  It can be re-applied if desired.
	 *
	 * @param menu          Handle to the menu.
	 * @param itemsPerPage  Number of items per page, or MENU_NO_PAGINATION.
	 * @return              True on success, false if pagination is too high or
	 *                      low.
	 * @error               Invalid Handle.
	 */
	static bool SetMenuPagination(Handle menu, int itemsPerPage)
	{
		return ExecFunc(s_SetMenuPaginationFunc, menu, itemsPerPage);
	}

	/**
	 * @brief Returns a menu's pagination setting.
	 *
	 * @param menu          Handle to the menu.
	 * @return              Pagination setting.
	 * @error               Invalid Handle.
	 */
	static int GetMenuPagination(Handle menu)
	{
		return ExecFunc(s_GetMenuPaginationFunc, menu);
	}

	/**
	 * @brief Returns a menu's MenuStyle Handle.  The Handle
	 * is global and cannot be freed.
	 *
	 * @param menu          Handle to the menu.
	 * @return              Handle to the menu's draw style.
	 * @error               Invalid Handle.
	 */
	static Handle GetMenuStyle(Handle menu)
	{
		return ExecFunc(s_GetMenuStyleFunc, menu);
	}

	/**
	 * @brief Sets the menu's default title/instruction message.
	 *
	 * @param menu          Menu Handle.
	 * @param format        Message string format
	 * @param args          Message string arguments
	 * @error               Invalid Handle.
	 */
	template<typename ... Args>
	static void SetMenuTitle(Handle menu, const char* format, Args ... args)
	{
		PushArg(s_SetMenuTitleFunc, menu);
		PushArg(s_SetMenuTitleFunc, format);
		SetMenuTitleSub(args...);
	}
private:
	static void SetMenuTitleSub()
	{
		ExecFunc(s_SetMenuTitleFunc);
	}

	template<typename T, typename ... Args>
	static void SetMenuTitleSub(T arg, Args ... args)
	{
		PushArgRef(s_SetMenuTitleFunc, arg);
		SetMenuTitleSub(args...);
	}
public:

	/**
	 * @brief Returns the text of a menu's title.
	 *
	 * @param menu          Menu Handle.
	 * @param buffer        Buffer to store title.
	 * @param maxlength     Maximum length of the buffer.
	 * @return              Number of bytes written.
	 * @error               Invalid Handle/
	 */
	static int GetMenuTitle(Handle menu, char* buffer, int maxlength)
	{
		PushArg(s_GetMenuStyleFunc, menu);
		PushArg(s_GetMenuStyleFunc, buffer, maxlength);
		PushArg(s_GetMenuStyleFunc, maxlength);
		return ExecFunc(s_GetMenuStyleFunc);
	}

	/**
	 * @brief Creates a raw MenuPanel based off the menu's style.
	 * The Handle must be freed with CloseHandle().
	 *
	 * @param menu          Menu Handle.
	 * @return              A new MenuPanel Handle.
	 * @error               Invalid Handle.
	 */
	static PanelHandle CreatePanelFromMenu(Handle menu)
	{
		return ExecFunc(s_CreatePanelFromMenuFunc, menu);
	}

	/**
	 * @brief Returns whether or not the menu has an exit button.
	 * By default, menus have an exit button.
	 *
	 * @param menu          Menu Handle.
	 * @return              True if the menu has an exit button; false otherwise.
	 * @error               Invalid Handle.
	 */
	static bool GetMenuExitButton(Handle menu)
	{
		return ExecFunc(s_GetMenuExitButtonFunc, menu);
	}

	/**
	 * @brief Sets whether or not the menu has an exit button.  By default, paginated menus
	 * have an exit button.
	 *
	 * If a menu's pagination is changed to MENU_NO_PAGINATION, and the pagination
	 * was previously a different value, then the Exit button status is changed to
	 * false.  It must be explicitly re-enabled afterwards.
	 *
	 * If a non-paginated menu has an exit button, then at most 9 items will be
	 * displayed.
	 *
	 * @param menu          Menu Handle.
	 * @param button        True to enable the button, false to remove it.
	 * @return              True if allowed; false on failure.
	 * @error               Invalid Handle.
	 */
	static bool SetMenuExitButton(Handle menu, bool button)
	{
		return ExecFunc(s_SetMenuExitButtonFunc, menu, button);
	}

	/**
	 * @brief Returns whether or not the menu has an "exit back" button.  By default,
	 * menus do not have an exit back button.
	 *
	 * Exit Back buttons appear as "Back" on page 1 of paginated menus and have
	 * functionality defined by the user in MenuEnd_ExitBack.
	 *
	 * @param menu          Menu Handle.
	 * @return              True if the menu has an exit back button; false otherwise.
	 * @error               Invalid Handle.
	 */
	static bool GetMenuExitBackButton(Handle menu)
	{
		return ExecFunc(s_GetMenuExitBackButtonFunc, menu);
	}

	/**
	 * @brief Sets whether or not the menu has an "exit back" button. By default, menus
	 * do not have an exit back button.
	 *
	 * Exit Back buttons appear as "Back" on page 1 of paginated menus and have
	 * functionality defined by the user in MenuEnd_ExitBack.
	 *
	 * @param menu          Menu Handle.
	 * @param button        True to enable the button, false to remove it.
	 * @error               Invalid Handle.
	 */
	static void SetMenuExitBackButton(Handle menu, bool button)
	{
		ExecFunc(s_SetMenuExitBackButtonFunc, menu, button);
	}

	/**
	 * @brief Sets whether or not the menu has a "no vote" button in slot 1.
	 * By default, menus do not have a no vote button.
	 *
	 * @param menu          Menu Handle.
	 * @param button        True to enable the button, false to remove it.
	 * @return              True if allowed; false on failure.
	 * @error               Invalid Handle.
	 */
	static bool SetMenuNoVoteButton(Handle menu, bool button)
	{
		return ExecFunc(s_SetMenuNoVoteButtonFunc, menu, button);
	}

	/**
	 * @brief Cancels a menu from displaying on all clients.  While the
	 * cancellation is in progress, this menu cannot be re-displayed
	 * to any clients.
	 *
	 * The menu may still exist on the client's screen after this command.
	 * This simply verifies that the menu is not being used anywhere.
	 *
	 * If any vote is in progress on a menu, it will be cancelled.
	 *
	 * @param menu          Menu Handle.
	 * @error               Invalid Handle.
	 */
	static void CancelMenu(Handle menu)
	{
		ExecFunc(s_CancelMenuFunc, menu);
	}

	/**
	 * @brief Retrieves a menu's option flags.
	 *
	 * @param menu          Menu Handle.
	 * @return              A bitstring of MENUFLAG bits.
	 * @error               Invalid Handle.
	 */
	static int GetMenuOptionFlags(Handle menu)
	{
		return ExecFunc(s_GetMenuOptionFlagsFunc, menu);
	}

	/**
	 * @brief Sets a menu's option flags.
	 *
	 * If a certain bit is not supported, it will be stripped before being set.
	 * See SetMenuExitButton() for information on Exit buttons.
	 * See SetMenuExitBackButton() for information on Exit Back buttons.
	 *
	 * @param menu          Menu Handle.
	 * @param flags         A new bitstring of MENUFLAG bits.
	 * @error               Invalid Handle.
	 */
	static void SetMenuOptionFlags(Handle menu, int flags)
	{
		ExecFunc(s_SetMenuOptionFlagsFunc, menu, flags);
	}

	/**
	 * @brief Returns whether a vote is in progress.
	 *
	 * @param menu          Deprecated; no longer used.
	 * @return              True if a vote is in progress, false otherwise.
	 */
	static bool IsVoteInProgress(Handle menu = INVALID_HANDLE)
	{
		return ExecFunc(s_IsVoteInProgressFunc, menu);
	}

	/**
	 * @brief Cancels the vote in progress.
	 *
	 * @error               If no vote is in progress.
	 */
	static void CancelVote()
	{
		ExecFunc(s_CancelVoteFunc);
	}

	/**
	 * @brief Broadcasts a menu to a list of clients.  The most selected item will be
	 * returned through MenuAction_End.  On a tie, a random item will be returned
	 * from a list of the tied items.
	 *
	 * Note that MenuAction_VoteEnd and MenuAction_VoteStart are both
	 * default callbacks and do not need to be enabled.
	 *
	 * @param menu          Menu Handle.
	 * @param clients       Array of clients to broadcast to.
	 * @param numClients    Number of clients in the array.
	 * @param time          Maximum time to leave menu on the screen.
	 * @param flags         Optional voting flags.
	 * @return              True on success, false if this menu already has a vote session
	 *                      in progress.
	 * @error               Invalid Handle, or a vote is already in progress.
	 */
	static bool VoteMenu(Handle menu, int clients[], int numClients, int time, int flags = 0)
	{
		PushArg(s_VoteMenuFunc, menu);
		PushArg(s_VoteMenuFunc, clients, numClients);
		PushArg(s_VoteMenuFunc, numClients);
		PushArg(s_VoteMenuFunc, time);
		PushArg(s_VoteMenuFunc, flags);
		return ExecFunc(s_VoteMenuFunc);
	}

	/**
	 * @brief Sends a vote menu to all clients.  See VoteMenu() for more information.
	 *
	 * @param menu          Menu Handle.
	 * @param time          Maximum time to leave menu on the screen.
	 * @param flags         Optional voting flags.
	 * @return              True on success, false if this menu already has a vote session
	 *                      in progress.
	 * @error               Invalid Handle.
	 */
	static bool VoteMenuToAll(Handle menu, int time, int flags = 0)
	{
		int total;
		int* players = new int[s_MaxClients];
		for (int i = 1; i <= s_MaxClients; ++i)
		{
			if (!IsClientInGame(i) || IsFakeClient(i))
				continue;
			players[total++] = i;
		}

		return VoteMenu(menu, players, total, time, flags);
	}

	/**
	 * @brief Sets an advanced vote handling callback.  If this callback is set,
	 * MenuAction_VoteEnd will not be called.
	 *
	 * @param menu          Menu Handle.
	 * @param callback      Callback function.
	 * @error               Invalid Handle or callback.
	 */
	static void SetVoteResultCallback(Handle menu, VoteHandler callback)
	{
		s_VoteHandlers[menu] = callback;
		ExecFunc(s_SetVoteResultCallbackFunc, menu);
	}

	/**
	 * @brief Returns the number of seconds you should "wait" before displaying
	 * a publicly invocable menu.  This number is the time remaining until
	 * (last_vote + sm_vote_delay).
	 *
	 * @return              Number of seconds to wait, or 0 for none.
	 */
	static int CheckVoteDelay()
	{
		return ExecFunc(s_CheckVoteDelayFunc);
	}

	/**
	 * @brief Returns whether a client is in the pool of clients allowed
	 * to participate in the current vote.  This is determined by
	 * the client list passed to VoteMenu().
	 *
	 * @param client        Client index.
	 * @return              True if client is allowed to vote, false otherwise.
	 * @error               If no vote is in progress or client index is invalid.
	 */
	static bool IsClientInVotePool(int client)
	{
		return ExecFunc(s_IsClientInVotePoolFunc, client);
	}

	/**
	 * @brief Redraws the current vote menu to a client in the voting pool.
	 *
	 * @param client        Client index.
	 * @param revotes       True to allow revotes, false otherwise.
	 * @return              True on success, false if the client is in the vote pool
	 *                      but cannot vote again.
	 * @error               No vote in progress, int client is not in the voting pool,
	 *                      or client index is invalid.
	 */
	static bool RedrawClientVoteMenu(int client, bool revotes = true)
	{
		return ExecFunc(s_RedrawClientVoteMenuFunc, client, revotes);
	}

	/**
	 * @brief Returns a style's global Handle.
	 *
	 * @param style         Menu Style.
	 * @return              A Handle, or INVALID_HANDLE if not found or unusable.
	 */
	static Handle GetMenuStyleHandle(MenuStyle style)
	{
		return ExecFunc(s_GetMenuStyleHandleFunc, style);
	}

	/**
	 * @brief Creates a MenuPanel from a MenuStyle.  Panels are used for drawing raw
	 * menus without any extra helper functions.  The Handle must be closed
	 * with CloseHandle().
	 *
	 * @param hStyle        MenuStyle Handle, or INVALID_HANDLE to use the default style.
	 * @return              A new MenuPanel Handle.
	 * @error               Invalid Handle other than INVALID_HANDLE.
	 */
	static PanelHandle CreatePanel(Handle hStyle = INVALID_HANDLE)
	{
		return ExecFunc(s_CreatePanelFunc, hStyle);
	}

	/**
	 * @brief Creates a Menu from a MenuStyle.  The Handle must be closed with
	 * CloseHandle().
	 *
	 * @param hStyle        MenuStyle Handle, or INVALID_HANDLE to use the default style.
	 * @param handler       Function which will receive menu actions.
	 * @param actions       Optionally set which actions to receive.  Select,
	 *                      Cancel, and End will always be received regardless
	 *                      of whether they are set or not.  They are also
	 *                      the only default actions.
	 * @return              A new menu Handle.
	 * @error               Invalid Handle other than INVALID_HANDLE.
	 */
	static MenuHandle CreateMenuEx(Handle hStyle = INVALID_HANDLE, MenuAction actions = MENU_ACTIONS_DEFAULT)
	{
		return ExecFunc(s_CreateMenuExFunc, hStyle, actions);
	}

	/**
	 * @brief Returns whether a client is viewing a menu.
	 *
	 * @param client        Client index.
	 * @param hStyle        MenuStyle Handle, or INVALID_HANDLE to use the default style.
	 * @return              A MenuSource value.
	 * @error               Invalid Handle other than null.
	 */
	static MenuSource GetClientMenu(int client, Handle hStyle = INVALID_HANDLE)
	{
		return static_cast<MenuSource>(ExecFunc(s_GetClientMenuFunc, client, hStyle));
	}

	/**
	 * @brief Cancels a menu on a client.  This will only affect non-external menus.
	 *
	 * @param client        Client index.
	 * @param autoIgnore    If true, no menus can be re-drawn on the client during
	 *                      the cancellation process.
	 * @param hStyle        MenuStyle Handle, or INVALID_HANDLE to use the default style.
	 * @return              True if a menu was cancelled, false otherwise.
	 */
	static bool CancelClientMenu(int client, bool autoIgnore = false, Handle hStyle = INVALID_HANDLE)
	{
		return ExecFunc(s_CancelClientMenuFunc, client, autoIgnore, hStyle);
	}

	/**
	 * @brief Returns a style's maximum items per page.
	 *
	 * @param hStyle        MenuStyle Handle, or INVALID_HANDLE to use the default style.
	 * @return              Maximum items per page.
	 * @error               Invalid Handle other than INVALID_HANDLE.
	 */
	static int GetMaxPageItems(Handle hStyle = INVALID_HANDLE)
	{
		return ExecFunc(s_GetMaxPageItemsFunc, hStyle);
	}

	/**
	 * @brief Returns a MenuPanel's parent style.
	 *
	 * @param panel         A MenuPanel Handle.
	 * @return              The MenuStyle Handle that created the panel.
	 * @error               Invalid Handle.
	 */
	static Handle GetPanelStyle(Handle panel)
	{
		return ExecFunc(s_GetPanelStyleFunc, panel);
	}

	/**
	 * @brief Sets the panel's title.
	 *
	 * @param panel         A MenuPanel Handle.
	 * @param text          Text to set as the title.
	 * @param onlyIfEmpty   If true, the title will only be set if no title is set.
	 * @error               Invalid Handle.
	 */
	static void SetPanelTitle(Handle panel, const char* text, bool onlyIfEmpty = false)
	{
		ExecFunc(s_SetPanelTitleFunc, panel, text, onlyIfEmpty);
	}

	/**
	 * @brief Draws an item on a panel.  If the item takes up a slot, the position
	 * is returned.
	 *
	 * @param panel         A MenuPanel Handle.
	 * @param text          Display text to use.  If not a raw line,
	 *                      the style may automatically add color markup.
	 *                      No numbering or newlines are needed.
	 * @param style         ITEMDRAW style flags.
	 * @return              A slot position, or 0 if item was a rawline or could not be drawn.
	 * @error               Invalid Handle.
	 */
	static int DrawPanelItem(Handle panel, const char* text, int style = ITEMDRAW_DEFAULT)
	{
		return ExecFunc(s_DrawPanelItemFunc, panel, text, style);
	}

	/**
	 * @brief Draws a raw line of text on a panel, without any markup other than a newline.
	 *
	 * @param panel         A MenuPanel Handle, or INVALID_HANDLE if inside a
	 *                      MenuAction_DisplayItem callback.
	 * @param text          Display text to use.
	 * @return              True on success, false if raw lines are not supported.
	 * @error               Invalid Handle.
	 */
	static bool DrawPanelText(Handle panel, const char* text)
	{
		return ExecFunc(s_DrawPanelTextFunc, panel, text);
	}

	/**
	 * @brief Returns whether or not the given drawing flags are supported by
	 * the menu style.
	 *
	 * @param panel         A MenuPanel Handle.
	 * @param style         ITEMDRAW style flags.
	 * @return              True if item is drawable, false otherwise.
	 * @error               Invalid Handle.
	 */
	static bool CanPanelDrawFlags(Handle panel, int style)
	{
		return ExecFunc(s_CanPanelDrawFlagsFunc, panel, style);
	}

	/**
	 * @brief Sets the selectable key map of a panel.  This is not supported by
	 * all styles (only by Radio, as of this writing).
	 *
	 * @param panel         A MenuPanel Handle.
	 * @param keys          An integer where each bit N allows key
	 *                      N+1 to be selected.  If no keys are selectable,
	 *                      then key 0 (bit 9) is automatically set.
	 * @return              True if supported, false otherwise.
	 */
	static bool SetPanelKeys(Handle panel, int keys)
	{
		return ExecFunc(s_SetPanelKeysFunc, panel, keys);
	}

	/**
	 * @brief Sends a panel to a client.  Unlike full menus, the handler
	 * function will only receive the following actions, both of
	 * which will have INVALID_HANDLE for a menu, and the client
	 * as param1.
	 *
	 * MenuAction_Select (param2 will be the key pressed)
	 * MenuAction_Cancel (param2 will be the reason)
	 *
	 * Also, if the menu fails to display, no callbacks will be called.
	 *
	 * @param panel         A MenuPanel Handle.
	 * @param client        A client to draw to.
	 * @param handler       The MenuHandler function to catch actions with.
	 * @param time          Time to hold the menu for.
	 * @return              True on success, false on failure.
	 * @error               Invalid Handle.
	 */
	static bool SendPanelToClient(Handle panel, int client, MenuHandler handler, int time)
	{
		Handle handle = ExecFunc(s_SendPanelToClientFunc, panel, client, time);
		s_MenuHandlers[handle] = handler;
		return handle;
	}

	/**
	 * @brief Returns the amount of text the menu can still hold.  If this is
	 * limit is reached or overflowed, the text is silently truncated.
	 *
	 * Radio menus: Currently 511 characters (512 bytes).
	 * Valve menus: Currently -1 (no meaning).
	 *
	 * @param panel         A MenuPanel Handle.
	 * @return              Number of characters that the menu can still hold,
	 *                      or -1 if there is no known limit.
	 * @error               Invalid Handle.
	 */
	static int GetPanelTextRemaining(Handle panel)
	{
		return ExecFunc(s_GetPanelTextRemainingFunc, panel);
	}

	/**
	 * @brief Returns the current key position.
	 *
	 * @param panel         A MenuPanel Handle.
	 * @return              Current key position starting at 1.
	 * @error               Invalid Handle.
	 */
	static int GetPanelCurrentKey(Handle panel)
	{
		return ExecFunc(s_GetPanelCurrentKeyFunc, panel);
	}

	/**
	 * @brief Sets the next key position.  This cannot be used
	 * to traverse backwards.
	 *
	 * @param panel         A MenuPanel Handle.
	 * @param key           Key that is greater or equal to
	 *                      GetPanelCurrentKey().
	 * @return              True on success, false otherwise.
	 * @error               Invalid Handle.
	 */
	static bool SetPanelCurrentKey(Handle panel, int key)
	{
		return ExecFunc(s_SetPanelCurrentKeyFunc, panel, key);
	}

	/**
	 * @brief Redraws menu text from inside a MenuAction_DisplayItem callback.
	 *
	 * @param text          Menu text to draw.
	 * @return              Item position; must be returned via the callback.
	 */
	static int RedrawMenuItem(const char* text)
	{
		return ExecFunc(s_RedrawMenuItemFunc, text);
	}

	/**
	 * @brief This function is provided for legacy code only.  Some older plugins may use
	 * network messages instead of the panel API.  This function wraps the panel
	 * API for eased portability into the SourceMod menu system.
	 *
	 * This function is only usable with the Radio Menu style.  You do not need to
	 * split up your menu into multiple packets; SourceMod will break the string
	 * up internally.
	 *
	 * @param client        Client index.
	 * @param str           Full menu string as would be passed over the network.
	 * @param time          Time to hold the menu for.
	 * @param keys          Selectable key bitstring.
	 * @return              True on success, false on failure.
	 * @error               Invalid client index, or radio menus not supported.
	 */
	static bool InternalShowMenu(int client, const char* str, int time, int keys = -1)
	{
		return ExecFunc(s_InternalShowMenuFunc, client, str, time, keys);
	}

	/**
	 * @brief Retrieves voting information from MenuAction_VoteEnd.
	 *
	 * @param param2        Second parameter of MenuAction_VoteEnd.
	 * @param winningVotes  Number of votes received by the winning option.
	 * @param totalVotes    Number of total votes received.
	 */
	static void GetMenuVoteInfo(int param2, int& winningVotes, int& totalVotes)
	{
		winningVotes = param2 & 0xFFFF;
		totalVotes = param2 >> 16;
	}

	/**
	 * @brief Quick stock to determine whether voting is allowed. This doesn't let you
	 * fine-tune a reason for not voting, so it's not recommended for lazily
	 * telling clients that voting isn't allowed.
	 *
	 * @return              True if voting is allowed, false if voting is in progress
	 *                      or the cooldown is active.
	 */
	static bool IsNewVoteAllowed()
	{
		if (IsVoteInProgress() || CheckVoteDelay() != 0)
			return false;
		return true;
	}
