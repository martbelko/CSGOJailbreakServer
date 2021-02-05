public:
	/**
	 * @brief Creates a basic timer.  Calling CloseHandle() on a timer will end the timer.
	 *
	 * @param interval      Interval from the current game time to execute the given function.
	 * @param func          Function to execute once the given interval has elapsed.
	 * @param data          Handle or value to pass through to the timer callback function.
	 * @param flags         Flags to set (such as repeatability or auto-Handle closing).
	 * @return              Handle to the timer object.  You do not need to call CloseHandle().
	 *                      If the timer could not be created, INVALID_HANDLE will be returned.
	 */
	static Handle CreateTimer(float interval, TimerCallbackFunc callback, void* data = nullptr, int flags = 0)
	{
		Handle timerHandle = ExecFunc(s_CreateTimerFunc, interval, reinterpret_cast<int>(data), flags);
		s_TimerCallbacks[timerHandle] = callback;
		return timerHandle;
	}

	/**
	 * @brief Kills a timer.  Use this instead of CloseHandle() if you need more options.
	 *
	 * @param timer         Timer Handle to kill.
	 * @param autoClose     If autoClose is true, the data that was passed to CreateTimer() will
	 *                      be closed as a handle if TIMER_DATA_HNDL_CLOSE was not specified.
	 * @error               Invalid handles will cause a run time error.
	 */
	static void KillTimer(Handle timer, bool autoClose = false)
	{
		ExecFunc(s_KillTimerFunc, timer, autoClose);
	}

	/**
	 * @brief Manually triggers a timer so its function will be called.
	 *
	 * @param timer         Timer Handle to trigger.
	 * @param reset         If reset is true, the elapsed time counter is reset
	 *                      so the full interval must pass again.
	 */
	static void TriggerTimer(Handle timer, bool reset = false)
	{
		ExecFunc(s_TriggerTimerFunc, timer, reset);
	}

	/**
	 * @brief Returns the simulated game time.
	 *
	 * This time is internally maintained by SourceMod and is based on the game
	 * tick count and tick rate.  Unlike GetGameTime(), it will increment past
	 * map changes and while no players are connected.  Unlike GetEngineTime(),
	 * it will not increment based on the system clock (i.e. it is still bound
	 * to the ticking process).
	 *
	 * @return              Time based on the game tick count.
	 */
	static float GetTickedTime()
	{
		return ExecAndReturn(s_GetTickedTimeFunc);
	}

	/**
	 * @brief Returns an estimate of the time left before the map ends.  If the server
	 * has not processed any frames yet (i.e. no players have joined the map yet),
	 * then the time left returned will always be infinite.
	 *
	 * @param timeleft      Variable to store the time, in seconds.  If the
	 *                      value is less than 0, the time limit is infinite.
	 * @return              True if the operation is supported, false otherwise.
	 */
	static bool GetMapTimeLeft(int& timeleft)
	{
		s_GetMapTimeLeftFunc->PushCellByRef(&timeleft);
		return ExecAndReturn(s_GetMapTimeLeftFunc);
	}

	/**
	 * @brief Retrieves the current map time limit.  If the server has not processed any
	 * frames yet (i.e. no players have joined the map yet), then the time limit
	 * returned will always be 0.
	 *
	 * @param time          Set to the number of total seconds in the map time
	 *                      limit, or 0 if there is no time limit set.
	 * @return              True on success, false if operation is not supported.
	 */
	static bool GetMapTimeLimit(int& time)
	{
		s_GetMapTimeLimitFunc->PushCellByRef(&time);
		return ExecAndReturn(s_GetMapTimeLimitFunc);
	}

	/**
	 * @brief Extends the map time limit in a way that will notify all plugins.
	 *
	 * @param time          Number of seconds to extend map time limit by.
	 *                      The number can be negative to decrease the time limit.
	 *                      If 0, the map will be set to have no time limit.
	 * @return              True on success, false if operation is not supported.
	 */
	static bool ExtendMapTimeLimit(int time)
	{
		return ExecFunc(s_ExtendMapTimeLimitFunc, time);
	}

	/**
	 * @brief Returns the number of seconds in between game server ticks.
	 *
	 * Note: A tick, in this context, is a frame.
	 *
	 * @return              Number of seconds in between ticks.
	 */
	static float GetTickInterval()
	{
		return ExecAndReturn(s_GetTickIntervalFunc);
	}

	/**
	 * @brief Returns whether or not the server is processing frames or not.
	 *
	 * The server does not process frames until at least one client joins the game.
	 * If server hibernation is disabled, once the first player has joined, even if that player
	 * leaves, the server's timers and entities will continue to work.
	 *
	 * @return              True if the server is ticking, false otherwise.
	 */
	static bool IsServerProcessing()
	{
		return ExecAndReturn(s_IsServerProcessingFunc);
	}
