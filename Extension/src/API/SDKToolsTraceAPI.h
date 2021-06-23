public:
	/**
	 * @brief Get the contents mask and the entity index at the given position.
	 *
	 * @param pos           World position to test.
	 * @param entindex      Entity index found at the given position (by reference).
	 * @return              Contents mask.
	 */
	static int TR_GetPointContents(const float pos[3], int& entindex = NULL_VALUE)
	{
		PushArg(s_TR_GetPointContentsFunc, pos, 3);
		PushArgRef(s_TR_GetPointContentsFunc, entindex);
		return ExecFunc(s_TR_GetPointContentsFunc);
	}

	/**
	 * @brief Get the point contents testing only the given entity index.
	 *
	 * @param entindex      Entity index to test.
	 * @param pos           World position.
	 * @return              Contents mask.
	 */
	static int TR_GetPointContentsEnt(int entindex, const float pos[3])
	{
		PushArg(s_TR_GetPointContentsEntFunc, entindex);
		PushArg(s_TR_GetPointContentsEntFunc, pos, 3);
		return ExecFunc(s_TR_GetPointContentsEntFunc);
	}

	/**
	 * @brief Starts up a new trace ray using a global trace result.
	 *
	 * @param pos           Starting position of the ray.
	 * @param vec           Depending on RayType, it will be used as the
	 *                      ending point, or the direction angle.
	 * @param flags         Trace flags.
	 * @param rtype         Method to calculate the ray direction.
	 */
	static void TR_TraceRay(const float pos[3], const float vec[3], int flags, RayType rtype)
	{
		PushArg(s_TR_TraceRayFunc, pos, 3);
		PushArg(s_TR_TraceRayFunc, vec, 3);
		PushArg(s_TR_TraceRayFunc, flags);
		PushArg(s_TR_TraceRayFunc, rtype);
		ExecFunc(s_TR_TraceRayFunc);
	}

	/**
	 * @brief Starts up a new trace hull using a global trace result.
	 *
	 * @param pos           Starting position of the ray.
	 * @param vec           Ending position of the ray.
	 * @param mins          Hull minimum size.
	 * @param maxs          Hull maximum size.
	 * @param flags         Trace flags.
	 */
	static void TR_TraceHull(const float pos[3], const float vec[3], const float mins[3], const float maxs[3], int flags)
	{
		PushArg(s_TR_TraceHullFunc, pos, 3);
		PushArg(s_TR_TraceHullFunc, vec, 3);
		PushArg(s_TR_TraceHullFunc, mins, 3);
		PushArg(s_TR_TraceHullFunc, maxs, 3);
		PushArg(s_TR_TraceHullFunc, flags);
		ExecFunc(s_TR_TraceHullFunc);
	}

	/**
	 * @brief Enumerates over entities along a ray. This may find entities that are
	 * close to the ray but do not actually intersect it. Use TR_Clip*RayToEntity
	 * with TR_DidHit to check if the ray actually intersects the entity.
	 *
	 * @param pos           Starting position of the ray.
	 * @param vec           Depending on RayType, it will be used as the ending
	 *                      point, or the direction angle.
	 * @param mask          Mask to use for the trace. See PARTITION_* flags.
	 * @param rtype         Method to calculate the ray direction.
	 * @param enumerator    Function to use as enumerator. For each entity found
	 *                      along the ray, this function is called.
	 * @param data          Arbitrary data value to pass through to the enumerator.
	 */
	static void TR_EnumerateEntities(const float pos[3], const float vec[3], int mask,
		RayType rtype, TraceEntityEnumeratorFunc enumerator, void* data = nullptr)
	{
		s_TraceEntityEnumeratorData[s_TraceEntityEnumeratorIndex] = data;
		s_TraceEntityEnumeratorCallbacks[s_TraceEntityEnumeratorIndex] = enumerator;

		PushArg(s_TR_EnumerateEntitiesFunc, pos, 3);
		PushArg(s_TR_EnumerateEntitiesFunc, vec, 3);
		PushArg(s_TR_EnumerateEntitiesFunc, mask);
		PushArg(s_TR_EnumerateEntitiesFunc, rtype);
		PushArg(s_TR_EnumerateEntitiesFunc, s_TraceEntityEnumeratorIndex);
		++s_TraceEntityEnumeratorIndex;
		ExecFunc(s_TR_EnumerateEntitiesFunc);
	}

	/**
	 * @brief Enumerates over entities along a ray hull. This may find entities that are
	 * close to the ray but do not actually intersect it. Use TR_Clip*RayToEntity
	 * with TR_DidHit to check if the ray actually intersects the entity.
	 *
	 * @param pos           Starting position of the ray.
	 * @param vec           Ending position of the ray.
	 * @param mins          Hull minimum size.
	 * @param maxs          Hull maximum size.
	 * @param mask          Mask to use for the trace. See PARTITION_* flags.
	 * @param enumerator    Function to use as enumerator. For each entity found
	 *                      along the ray, this function is called.
	 * @param data          Arbitrary data value to pass through to the enumerator.
	 */
	static void TR_EnumerateEntitiesHull(const float pos[3], const float vec[3], const float mins[3],
		const float maxs[3], int mask, TraceEntityEnumeratorFunc enumerator, void* data = nullptr)
	{
		s_TraceEntityEnumeratorData[s_TraceEntityEnumeratorIndex] = data;
		s_TraceEntityEnumeratorCallbacks[s_TraceEntityEnumeratorIndex] = enumerator;

		PushArg(s_TR_EnumerateEntitiesHullFunc, pos, 3);
		PushArg(s_TR_EnumerateEntitiesHullFunc, vec, 3);
		PushArg(s_TR_EnumerateEntitiesHullFunc, mins, 3);
		PushArg(s_TR_EnumerateEntitiesHullFunc, maxs, 3);
		PushArg(s_TR_EnumerateEntitiesHullFunc, mask);
		PushArg(s_TR_EnumerateEntitiesHullFunc, s_TraceEntityEnumeratorIndex);
		++s_TraceEntityEnumeratorIndex;
		ExecFunc(s_TR_EnumerateEntitiesHullFunc);
	}

	/**
	 * @brief Starts up a new trace ray using a global trace result and a customized
	 * trace ray filter.
	 *
	 * Calling TR_Trace*Filter or TR_Trace*FilterEx from inside a filter
	 * function is currently not allowed and may not work.
	 *
	 * @param pos           Starting position of the ray.
	 * @param vec           Depending on RayType, it will be used as the ending
	 *                      point, or the direction angle.
	 * @param flags         Trace flags.
	 * @param rtype         Method to calculate the ray direction.
	 * @param filter        Function to use as a filter.
	 * @param data          Arbitrary data value to pass through to the filter
	 *                      function.
	 */
	static void TR_TraceRayFilter(const float pos[3], const float vec[3], int flags, RayType rtype, TraceEntityFilterFunc filter,
		void* data = nullptr)
	{
		s_TraceEntityFilterData[s_TraceEntityFilterIndex] = data;
		s_TraceEntityFilterCallbacks[s_TraceEntityFilterIndex] = filter;

		PushArg(s_TR_TraceRayFilterFunc, pos, 3);
		PushArg(s_TR_TraceRayFilterFunc, vec, 3);
		PushArg(s_TR_TraceRayFilterFunc, flags);
		PushArg(s_TR_TraceRayFilterFunc, rtype);
		PushArg(s_TR_TraceRayFilterFunc, s_TraceEntityFilterIndex);
		++s_TraceEntityFilterIndex;
		ExecFunc(s_TR_TraceRayFilterFunc);
	}

	/**
	 * @brief Starts up a new trace hull using a global trace result and a customized
	 * trace ray filter.
	 *
	 * Calling TR_Trace*Filter or TR_Trace*FilterEx from inside a filter
	 * function is currently not allowed and may not work.
	 *
	 * @param pos           Starting position of the ray.
	 * @param vec           Ending position of the ray.
	 * @param mins          Hull minimum size.
	 * @param maxs          Hull maximum size.
	 * @param flags         Trace flags.
	 * @param filter        Function to use as a filter.
	 * @param data          Arbitrary data value to pass through to the filter
	 *                      function.
	 */
	static void TR_TraceHullFilter(const float pos[3], const float vec[3], const float mins[3], const float maxs[3],
		int flags, TraceEntityFilterFunc filter, void* data = nullptr)
	{
		s_TraceEntityFilterData[s_TraceEntityFilterIndex] = data;
		s_TraceEntityFilterCallbacks[s_TraceEntityFilterIndex] = filter;

		PushArg(s_TR_TraceHullFilterFunc, pos, 3);
		PushArg(s_TR_TraceHullFilterFunc, vec, 3);
		PushArg(s_TR_TraceHullFilterFunc, mins, 3);
		PushArg(s_TR_TraceHullFilterFunc, maxs, 3);
		PushArg(s_TR_TraceHullFilterFunc, flags);
		PushArg(s_TR_TraceHullFilterFunc, s_TraceEntityFilterIndex);
		++s_TraceEntityFilterIndex;
		ExecFunc(s_TR_TraceHullFilterFunc);
	}

	/**
	 * @brief Clips a ray to a particular entity.
	 *
	 * @param pos           Starting position of the ray.
	 * @param vec           Depending on RayType, it will be used as the ending
	 *                      point, or the direction angle.
	 * @param flags         Trace flags.
	 * @param rtype         Method to calculate the ray direction.
	 * @param entity        Entity to clip to.
	 */
	static void TR_ClipRayToEntity(const float pos[3], const float vec[3], int flags, RayType rtype, int entity)
	{
		PushArg(s_TR_ClipRayToEntityFunc, pos, 3);
		PushArg(s_TR_ClipRayToEntityFunc, vec, 3);
		PushArg(s_TR_ClipRayToEntityFunc, flags);
		PushArg(s_TR_ClipRayToEntityFunc, rtype);
		PushArg(s_TR_ClipRayToEntityFunc, entity);
		ExecFunc(s_TR_ClipRayToEntityFunc);
	}

	/**
	 * @brief Clips a ray hull to a particular entity.
	 *
	 * @param pos           Starting position of the ray.
	 * @param vec           Ending position of the ray.
	 * @param mins          Hull minimum size.
	 * @param maxs          Hull maximum size.
	 * @param flags         Trace flags.
	 * @param entity        Entity to clip to.
	 */
	static void TR_ClipRayHullToEntity(const float pos[3], const float vec[3], const float mins[3], const float maxs[3],
		int flags, int entity)
	{
		PushArg(s_TR_ClipRayHullToEntityFunc, pos, 3);
		PushArg(s_TR_ClipRayHullToEntityFunc, vec, 3);
		PushArg(s_TR_ClipRayHullToEntityFunc, mins, 3);
		PushArg(s_TR_ClipRayHullToEntityFunc, maxs, 3);
		ExecFunc(s_TR_ClipRayHullToEntityFunc);
	}

	/**
	 * @brief Clips the current global ray (or hull) to a particular entity.
	 *
	 * @param flags         Trace flags.
	 * @param entity        Entity to clip to.
	 */
	static void TR_ClipCurrentRayToEntity(int flags, int entity)
	{
		ExecFunc(s_TR_ClipCurrentRayToEntityFunc, flags, entity);
	}

	/**
	 * @brief Starts up a new trace ray using a new trace result.
	 *
	 * @param pos           Starting position of the ray.
	 * @param vec           Depending on RayType, it will be used as the ending
	 *                      point, or the direction angle.
	 * @param flags         Trace flags.
	 * @param rtype         Method to calculate the ray direction.
	 * @return              Ray trace handle, which must be closed via CloseHandle().
	 */
	static Handle TR_TraceRayEx(const float pos[3], const float vec[3], int flags, RayType rtype)
	{
		PushArg(s_TR_TraceRayExFunc, pos, 3);
		PushArg(s_TR_TraceRayExFunc, vec, 3);
		PushArg(s_TR_TraceRayExFunc, flags);
		PushArg(s_TR_TraceRayExFunc, rtype);
		return ExecFunc(s_TR_TraceRayExFunc);
	}

	/**
	 * @brief Starts up a new trace hull using a new trace result.
	 *
	 * @param pos           Starting position of the ray.
	 * @param vec           Ending position of the ray.
	 * @param mins          Hull minimum size.
	 * @param maxs          Hull maximum size.
	 * @param flags         Trace flags.
	 * @return              Ray trace handle, which must be closed via CloseHandle().
	 */
	static Handle TR_TraceHullEx(const float pos[3], const float vec[3], const float mins[3], const float maxs[3], int flags)
	{
		PushArg(s_TR_TraceHullExFunc, pos, 3);
		PushArg(s_TR_TraceHullExFunc, vec, 3);
		PushArg(s_TR_TraceHullExFunc, mins, 3);
		PushArg(s_TR_TraceHullExFunc, maxs, 3);
		PushArg(s_TR_TraceHullExFunc, flags);
		return ExecFunc(s_TR_TraceHullExFunc);
	}

	/**
	 * @brief Starts up a new trace ray using a new trace result and a customized
	 * trace ray filter.
	 *
	 * Calling TR_Trace*Filter or TR_TraceRay*Ex from inside a filter
	 * function is currently not allowed and may not work.
	 *
	 * @param pos           Starting position of the ray.
	 * @param vec           Depending on RayType, it will be used as the ending
	 *                      point, or the direction angle.
	 * @param flags         Trace flags.
	 * @param rtype         Method to calculate the ray direction.
	 * @param filter        Function to use as a filter.
	 * @param data          Arbitrary data value to pass through to the filter function.
	 * @return              Ray trace handle, which must be closed via CloseHandle().
	 */
	static Handle TR_TraceRayFilterEx(const float pos[3], const float vec[3], int flags,
		RayType rtype, TraceEntityFilterFunc filter, void* data = nullptr)
	{
		s_TraceEntityFilterData[s_TraceEntityFilterIndex] = data;
		s_TraceEntityFilterCallbacks[s_TraceEntityFilterIndex] = filter;

		PushArg(s_TR_TraceRayFilterExFunc, pos, 3);
		PushArg(s_TR_TraceRayFilterExFunc, vec, 3);
		PushArg(s_TR_TraceRayFilterExFunc, flags);
		PushArg(s_TR_TraceRayFilterExFunc, rtype);
		PushArg(s_TR_TraceRayFilterExFunc, s_TraceEntityFilterIndex);
		++s_TraceEntityFilterIndex;
		return ExecFunc(s_TR_TraceRayFilterExFunc);
	}

	/**
	 * @brief Starts up a new trace hull using a new trace result and a customized
	 * trace ray filter.
	 *
	 * Calling TR_Trace*Filter or TR_Trace*FilterEx from inside a filter
	 * function is currently not allowed and may not work.
	 *
	 * @param pos           Starting position of the ray.
	 * @param vec           Ending position of the ray.
	 * @param mins          Hull minimum size.
	 * @param maxs          Hull maximum size.
	 * @param flags         Trace flags.
	 * @param filter        Function to use as a filter.
	 * @param data          Arbitrary data value to pass through to the filter function.
	 * @return              Ray trace handle, which must be closed via CloseHandle().
	 */
	static Handle TR_TraceHullFilterEx(const float pos[3], const float vec[3], const float mins[3], const float maxs[3],
		int flags, TraceEntityFilterFunc filter, void* data = nullptr)
	{
		s_TraceEntityFilterData[s_TraceEntityFilterIndex] = data;
		s_TraceEntityFilterCallbacks[s_TraceEntityFilterIndex] = filter;

		PushArg(s_TR_TraceHullFilterExFunc, pos, 3);
		PushArg(s_TR_TraceHullFilterExFunc, vec, 3);
		PushArg(s_TR_TraceHullFilterExFunc, mins, 3);
		PushArg(s_TR_TraceHullFilterExFunc, maxs, 3);
		PushArg(s_TR_TraceHullFilterExFunc, flags);
		PushArg(s_TR_TraceHullFilterExFunc, s_TraceEntityFilterIndex);
		++s_TraceEntityFilterIndex;
		return ExecFunc(s_TR_TraceHullFilterExFunc);
	}

	/**
	 * @brief Clips a ray to a particular entity.
	 *
	 * @param pos           Starting position of the ray.
	 * @param vec           Depending on RayType, it will be used as the ending
	 *                      point, or the direction angle.
	 * @param flags         Trace flags.
	 * @param rtype         Method to calculate the ray direction.
	 * @param entity        Entity to clip to.
	 * @return              Ray trace handle, which must be closed via CloseHandle().
	 */
	static Handle TR_ClipRayToEntityEx(const float pos[3], const float vec[3], int flags, RayType rtype, int entity)
	{
		PushArg(s_TR_ClipRayToEntityExFunc, pos, 3);
		PushArg(s_TR_ClipRayToEntityExFunc, vec, 3);
		PushArg(s_TR_ClipRayToEntityExFunc, flags);
		PushArg(s_TR_ClipRayToEntityExFunc, rtype);
		PushArg(s_TR_ClipRayToEntityExFunc, entity);
		return ExecFunc(s_TR_ClipRayToEntityExFunc);
	}

	/**
	 * @brief Clips a ray hull to a particular entity.
	 *
	 * @param pos           Starting position of the ray.
	 * @param vec           Ending position of the ray.
	 * @param mins          Hull minimum size.
	 * @param maxs          Hull maximum size.
	 * @param flags         Trace flags.
	 * @param entity        Entity to clip to.
	 * @return              Ray trace handle, which must be closed via CloseHandle().
	 */
	static Handle TR_ClipRayHullToEntityEx(const float pos[3], const float vec[3], const float mins[3],
		const float maxs[3], int flags, int entity)
	{
		PushArg(s_TR_ClipRayHullToEntityExFunc, pos, 3);
		PushArg(s_TR_ClipRayHullToEntityExFunc, vec, 3);
		PushArg(s_TR_ClipRayHullToEntityExFunc, mins, 3);
		PushArg(s_TR_ClipRayHullToEntityExFunc, maxs, 3);
		PushArg(s_TR_ClipRayHullToEntityExFunc, flags);
		PushArg(s_TR_ClipRayHullToEntityExFunc, entity);
		return ExecFunc(s_TR_ClipRayHullToEntityExFunc);
	}

	/**
	 * @brief Clips the current global ray (or hull) to a particular entity.
	 *
	 * @param flags         Trace flags.
	 * @param entity        Entity to clip to.
	 * @return              Ray trace handle, which must be closed via CloseHandle().
	 */
	static Handle TR_ClipCurrentRayToEntityEx(int flags, int entity)
	{
		return ExecFunc(s_TR_ClipCurrentRayToEntityExFunc, flags, entity);
	}

	/**
	 * @brief Returns the time fraction from a trace result (1.0 means no collision).
	 *
	 * @param hndl          A trace Handle, or INVALID_HANDLE to use a global trace result.
	 * @return              Time fraction value of the trace.
	 * @error               Invalid Handle.
	 */
	static float TR_GetFraction(Handle hndl = INVALID_HANDLE)
	{
		return ExecFunc(s_TR_GetFractionFunc, hndl);
	}

	/**
	 * @brief Returns the time fraction from a trace result when it left a solid.
	 * Only valid if trace started in solid
	 *
	 * @param hndl          A trace Handle, or INVALID_HANDLE to use a global trace result.
	 * @return              Time fraction left solid value of the trace.
	 * @error               Invalid Handle.
	 */
	static float TR_GetFractionLeftSolid(Handle hndl = INVALID_HANDLE)
	{
		return ExecFunc(s_TR_GetFractionLeftSolidFunc, hndl);
	}

	/**
	 * @brief Returns the starting position of a trace.
	 *
	 * @param hndl          A trace Handle, or INVALID_HANDLE to use a global trace result.
	 * @param pos           Vector buffer to store data in.
	 * @error               Invalid Handle.
	 */
	static void TR_GetStartPosition(Handle hndl, float pos[3])
	{
		PushArg(s_TR_GetStartPositionFunc, hndl);
		PushArg(s_TR_GetStartPositionFunc, pos, 3);
		ExecFunc(s_TR_GetStartPositionFunc);
	}

	/**
	 * @brief Returns the collision position of a trace result.
	 *
	 * @param pos           Vector buffer to store data in.
	 * @param hndl          A trace Handle, or INVALID_HANDLE to use a global trace result.
	 * @error               Invalid Handle.
	 */
	static void TR_GetEndPosition(float pos[3], Handle hndl = INVALID_HANDLE)
	{
		PushArg(s_TR_GetEndPositionFunc, pos, 3);
		PushArg(s_TR_GetEndPositionFunc, hndl);
		ExecFunc(s_TR_GetEndPositionFunc);
	}

	/**
	 * @brief Returns the entity index that collided with the trace.
	 *
	 * @param hndl          A trace Handle, or INVALID_HANDLE to use a global trace result.
	 * @return              Entity index or -1 for no collision.
	 * @error               Invalid Handle.
	 */
	static int TR_GetEntityIndex(Handle hndl = INVALID_HANDLE)
	{
		return ExecFunc(s_TR_GetEntityIndexFunc, hndl);
	}

	/**
	 * @brief Returns the displacement flags for the surface that was hit. See DISPSURF_FLAG_*.
	 *
	 * @param hndl          A trace Handle, or INVALID_HANDLE to use a global trace result.
	 * @return              Displacement flags.
	 * @error               Invalid Handle.
	 */
	static int TR_GetDisplacementFlags(Handle hndl = INVALID_HANDLE)
	{
		return ExecFunc(s_TR_GetDisplacementFlagsFunc, hndl);
	}

	/**
	 * @brief Returns the name of the surface that was hit.
	 *
	 * @param hndl          A trace Handle, or INVALID_HANDLE to use a global trace result.
	 * @param buffer        Buffer to store surface name in
	 * @param maxlen        Maximum length of output buffer
	 * @error               Invalid Handle.
	 */
	static void TR_GetSurfaceName(Handle hndl, char* buffer, int maxlen)
	{
		PushArg(s_TR_GetSurfaceNameFunc, hndl);
		PushArg(s_TR_GetSurfaceNameFunc, buffer, maxlen);
		PushArg(s_TR_GetSurfaceNameFunc, maxlen);
		ExecFunc(s_TR_GetSurfaceNameFunc);
	}

	/**
	 * @brief Returns the surface properties index of the surface that was hit.
	 *
	 * @param hndl          A trace Handle, or INVALID_HANDLE to use a global trace result.
	 * @return              Surface props.
	 * @error               Invalid Handle.
	 */
	static int TR_GetSurfaceProps(Handle hndl = INVALID_HANDLE)
	{
		return ExecFunc(s_TR_GetSurfacePropsFunc, hndl);
	}

	/**
	 * @brief Returns the surface flags. See SURF_*.
	 *
	 * @param hndl          A trace Handle, or INVALID_HANDLE to use a global trace result.
	 * @return              Surface flags.
	 * @error               Invalid Handle.
	 */
	static int TR_GetSurfaceFlags(Handle hndl = INVALID_HANDLE)
	{
		return ExecFunc(s_TR_GetSurfaceFlagsFunc, hndl);
	}

	/**
	 * @brief Returns the index of the physics bone that was hit.
	 *
	 * @param hndl          A trace Handle, or INVALID_HANDLE to use a global trace result.
	 * @return              Physics bone index.
	 * @error               Invalid Handle.
	 */
	static int TR_GetPhysicsBone(Handle hndl = INVALID_HANDLE)
	{
		return ExecFunc(s_TR_GetPhysicsBoneFunc, hndl);
	}

	/**
	 * @brief Returns whether the entire trace was in a solid area.
	 *
	 * @param hndl          A trace Handle, or INVALID_HANDLE to use a global trace result.
	 * @return              True if entire trace was in a solid area, otherwise false.
	 * @error               Invalid Handle.
	 */
	static bool TR_AllSolid(Handle hndl = INVALID_HANDLE)
	{
		return ExecFunc(s_TR_AllSolidFunc, hndl);
	}

	/**
	 * @brief Returns whether the initial point was in a solid area.
	 *
	 * @param hndl          A trace Handle, or INVALID_HANDLE to use a global trace result.
	 * @return              True if initial point was in a solid area, otherwise false.
	 * @error               Invalid Handle.
	 */
	static bool TR_StartSolid(Handle hndl = INVALID_HANDLE)
	{
		return ExecFunc(s_TR_StartSolidFunc, hndl);
	}

	/**
	 * @brief Returns if there was any kind of collision along the trace ray.
	 *
	 * @param hndl          A trace Handle, or INVALID_HANDLE to use a global trace result.
	 * @return              True if any collision found, otherwise false.
	 * @error               Invalid Handle.
	 */
	static bool TR_DidHit(Handle hndl = INVALID_HANDLE)
	{
		return ExecFunc(s_TR_DidHitFunc, hndl);
	}

	/**
	 * @brief Returns in which body hit group the trace collided if any.
	 *
	 * @param hndl          A trace Handle, or INVALID_HANDLE to use a global trace result.
	 * @return              Body hit group.
	 * @error               Invalid Handle.
	 */
	static int TR_GetHitGroup(Handle hndl = INVALID_HANDLE)
	{
		return ExecFunc(s_TR_GetHitGroupFunc, hndl);
	}

	/**
	 * @brief Returns in which hitbox the trace collided if any.
	 *
	 * Note: if the entity that collided with the trace is the world entity,
	 * then this function doesn't return an hitbox index but a static prop index.
	 *
	 * @param hndl          A trace Handle, or INVALID_HANDLE to use a global trace result.
	 * @return              Hitbox index (Or static prop index).
	 * @error               Invalid Handle.
	 */
	static int TR_GetHitBoxIndex(Handle hndl = INVALID_HANDLE)
	{
		return ExecFunc(s_TR_GetHitBoxIndexFunc, hndl);
	}

	/**
	 * @brief Find the normal vector to the collision plane of a trace.
	 *
	 * @param hndl          A trace Handle, or INVALID_HANDLE to use a global trace result.
	 * @param normal        Vector buffer to store the vector normal to the collision plane
	 * @error               Invalid Handle
	 */
	static void TR_GetPlaneNormal(Handle hndl, float normal[3])
	{
		PushArg(s_TR_GetPlaneNormalFunc, hndl);
		PushArg(s_TR_GetPlaneNormalFunc, normal, 3);
		ExecFunc(s_TR_GetPlaneNormalFunc);
	}

	/**
	 * @brief Tests a point to see if it's outside any playable area
	 *
	 * @param pos           Vector buffer to store data in.
	 * @return              True if outside world, otherwise false.
	 */
	static bool TR_PointOutsideWorld(float pos[3])
	{
		PushArg(s_TR_PointOutsideWorldFunc, pos, 3);
		return ExecFunc(s_TR_PointOutsideWorldFunc);
	}
