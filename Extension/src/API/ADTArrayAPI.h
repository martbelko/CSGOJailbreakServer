public:
	/**
	 * Given a maximum string size (including the null terminator),
	 * returns the number of cells required to fit that string.
	 *
	 * @param size          Number of bytes.
	 * @return              Minimum number of cells required to fit the byte count.
	 */
	static int ByteCountToCells(int size)
	{
		if (!size)
			return 1;
		return (size + 3) / 4;
	}

	/**
	 * @brief Creates a dynamic global cell array.  While slower than a normal array,
	 * it can be used globally AND dynamically, which is otherwise impossible.
	 *
	 * The contents of the array are uniform; i.e. storing a string at index X
	 * and then retrieving it as an integer is NOT the same as StringToInt()!
	 * The "blocksize" determines how many cells each array slot has; it cannot
	 * be changed after creation.
	 *
	 * @param blocksize     The number of cells each member of the array can
	 *                      hold.  For example, 32 cells is equivalent to:
	 *                      new Array[X][32]
	 * @param startsize     Initial size of the array.  Note that data will
	 *                      NOT be auto-initialized.
	 * @return              New Handle to the array object.
	 */
	static ArrayListHandle CreateArray(int blocksize = 1, int startsize = 0)
	{
		return ExecFunc(s_CreateArrayFunc, blocksize, startsize);
	}

	/**
	 * @brief Clears an array of all entries.  This is the same as ResizeArray(0).
	 *
	 * @param array         Array Handle.
	 * @error               Invalid Handle.
	 */
	static void ClearArray(Handle arr)
	{
		ExecFunc(s_ClearArrayFunc, arr);
	}

	/**
	 * @brief Clones an array, returning a new handle with the same size and data. This should NOT
	 * be confused with CloneHandle. This is a completely new handle with the same data but
	 * no relation to the original. You MUST close it.
	 *
	 * @param array         Array handle to be cloned
	 * @return              New handle to the cloned array object
	 * @error               Invalid Handle
	 */
	static Handle CloneArray(Handle arr)
	{
		return ExecFunc(s_CloneArrayFunc, arr);
	}

	/**
	 * @brief Resizes an array.  If the size is smaller than the current size,
	 * the array is truncated.  If the size is larger than the current size,
	 * the data at the additional indexes will not be initialized.
	 *
	 * @param array         Array Handle.
	 * @param newsize       New size.
	 * @error               Invalid Handle or out of memory.
	 */
	static void ResizeArray(Handle arr, int newsize)
	{
		ExecFunc(s_ResizeArrayFunc, arr, newsize);
	}

	/**
	 * @brief Returns the array size.
	 *
	 * @param array         Array Handle.
	 * @return              Number of elements in the array.
	 * @error               Invalid Handle.
	 */
	static int GetArraySize(Handle arr)
	{
		return ExecFunc(s_GetArraySizeFunc, arr);
	}

	/**
	 * @brief Pushes a value onto the end of an array, adding a new index.
	 *
	 * This may safely be used even if the array has a blocksize
	 * greater than 1.
	 *
	 * @param array         Array Handle.
	 * @param value         Value to push.
	 * @return              Index of the new entry.
	 * @error               Invalid Handle or out of memory.
	 */
	template<typename any>
	static int PushArrayCell(Handle arr, any value)
	{
		return ExecFunc(s_PushArrayCellFunc, arr, value);
	}

	/**
	 * @brief Pushes a string onto the end of an array, truncating it
	 * if it is too big.
	 *
	 * @param array         Array Handle.
	 * @param value         String to push.
	 * @return              Index of the new entry.
	 * @error               Invalid Handle or out of memory.
	 */
	static int PushArrayString(Handle arr, const char* value)
	{
		return ExecFunc(s_PushArrayStringFunc, arr, value);
	}

	/**
	 * @brief Pushes an array of cells onto the end of an array.  The cells
	 * are pushed as a block (i.e. the entire array sits at the index),
	 * rather than pushing each cell individually.
	 *
	 * @param array         Array Handle.
	 * @param values        Block of values to copy.
	 * @param size          If not set, the number of elements copied from the array
	 *                      will be equal to the blocksize.  If set higher than the
	 *                      blocksize, the operation will be truncated.
	 * @return              Index of the new entry.
	 * @error               Invalid Handle or out of memory.
	 */
	template<typename any>
	static int PushArrayArray(Handle arr, const any values[], int size = -1)
	{
		PushArg(s_PushArrayArrayFunc, arr);
		PushArg(s_PushArrayArrayFunc, values, size);
		PushArg(s_PushArrayArrayFunc, size);
		return ExecFunc(s_PushArrayArrayFunc);
	}

	/**
	 * @brief Retrieves a cell value from an array.
	 *
	 * @param array         Array Handle.
	 * @param index         Index in the array.
	 * @param block         Optionally specify which block to read from
	 *                      (useful if the blocksize > 0).
	 * @param asChar        Optionally read as a byte instead of a cell.
	 * @return              Value read.
	 * @error               Invalid Handle, invalid index, or invalid block.
	 */
	template<typename any>
	static any GetArrayCell(Handle arr, int index, int block = 0, bool asChar = false)
	{
		return ExecFunc(s_GetArrayCellFunc, arr, index, block, asChar);
	}

	/**
	 * @brief Retrieves a string value from an array.
	 *
	 * @param array         Array Handle.
	 * @param index         Index in the array.
	 * @param buffer        Buffer to copy to.
	 * @param maxlength     Maximum size of the buffer.
	 * @return              Number of characters copied.
	 * @error               Invalid Handle or invalid index.
	 */
	static int GetArrayString(Handle arr, int index, char* buffer, int maxlength)
	{
		PushArg(s_GetArrayStringFunc, arr);
		PushArg(s_GetArrayStringFunc, index);
		PushArg(s_GetArrayStringFunc, buffer, maxlength);
		PushArg(s_GetArrayStringFunc, maxlength);
		return ExecFunc(s_GetArrayStringFunc);
	}

	/**
	 * @brief Retrieves an array of cells from an array.
	 *
	 * @param array         Array Handle.
	 * @param index         Index in the array.
	 * @param buffer        Buffer to store the array in.
	 * @param size          If not set, assumes the buffer size is equal to the
	 *                      blocksize.  Otherwise, the size passed is used.
	 * @return              Number of cells copied.
	 * @error               Invalid Handle or invalid index.
	 */
	template<typename any>
	static int GetArrayArray(Handle arr, int index, any buffer[], int size = -1)
	{
		PushArg(s_GetArrayArrayFunc, arr);
		PushArg(s_GetArrayArrayFunc, index);
		PushArg(s_GetArrayArrayFunc, buffer, size);
		PushArg(s_GetArrayArrayFunc, size);
		return ExecFunc(s_GetArrayArrayFunc);
	}

	/**
	 * @brief Sets a cell value in an array.
	 *
	 * @param array         Array Handle.
	 * @param index         Index in the array.
	 * @param value         Cell value to set.
	 * @param block         Optionally specify which block to write to
	 *                      (useful if the blocksize > 0).
	 * @param asChar        Optionally set as a byte instead of a cell.
	 * @error               Invalid Handle, invalid index, or invalid block.
	 */
	template<typename any>
	static void SetArrayCell(Handle arr, int index, any value, int block = 0, bool asChar = false)
	{
		ExecFunc(s_SetArrayCellFunc, arr, index, value, block, asChar);
	}

	/**
	 * @brief Sets a string value in an array.
	 *
	 * @param array         Array Handle.
	 * @param index         Index in the array.
	 * @param value         String value to set.
	 * @return              Number of characters copied.
	 * @error               Invalid Handle or invalid index.
	 */
	static int SetArrayString(Handle arr, int index, const char* value)
	{
		return ExecFunc(s_SetArrayStringFunc, arr, index, value);
	}

	/**
	 * @brief Sets an array of cells in an array.
	 *
	 * @param array         Array Handle.
	 * @param index         Index in the array.
	 * @param values        Array to copy.
	 * @param size          If not set, assumes the buffer size is equal to the
	 *                      blocksize.  Otherwise, the size passed is used.
	 * @return              Number of cells copied.
	 * @error               Invalid Handle or invalid index.
	 */
	template<typename any>
	static int SetArrayArray(Handle arr, int index, const any values[], int size = -1)
	{
		PushArg(s_SetArrayArrayFunc, arr);
		PushArg(s_SetArrayArrayFunc, index);
		PushArg(s_SetArrayArrayFunc, values, size);
		PushArg(s_SetArrayArrayFunc, size);
		return ExecFunc(s_SetArrayArrayFunc);
	}

	/**
	 * @brief Shifts an array up.  All array contents after and including the given
	 * index are shifted up by one, and the given index is then "free."
	 * After shifting, the contents of the given index is undefined.
	 *
	 * @param array         Array Handle.
	 * @param index         Index in the array to shift up from.
	 * @error               Invalid Handle or invalid index.
	 */
	static void ShiftArrayUp(Handle arr, int index)
	{
		ExecFunc(s_ShiftArrayUpFunc, arr, index);
	}

	/**
	 * @brief Removes an array index, shifting the entire array down from that position
	 * on.  For example, if item 8 of 10 is removed, the last 3 items will then be
	 * (6,7,8) instead of (7,8,9), and all indexes before 8 will remain unchanged.
	 *
	 * @param array         Array Handle.
	 * @param index         Index in the array to remove at.
	 * @error               Invalid Handle or invalid index.
	 */
	static void RemoveFromArray(Handle arr, int index)
	{
		ExecFunc(s_RemoveFromArrayFunc, arr, index);
	}

	/**
	 * @brief Swaps two items in the array.
	 *
	 * @param array         Array Handle.
	 * @param index1        First index.
	 * @param index2        Second index.
	 * @error               Invalid Handle or invalid index.
	 */
	static void SwapArrayItems(Handle arr, int index1, int index2)
	{
		ExecFunc(s_SwapArrayItemsFunc, arr, index1, index2);
	}

	/**
	 * @brief Returns the index for the first occurrence of the provided string. If the string
	 * cannot be located, -1 will be returned.
	 *
	 * @param array         Array Handle.
	 * @param item          String to search for
	 * @return              Array index, or -1 on failure
	 * @error               Invalid Handle
	 */
	static int FindStringInArray(Handle arr, const char* item)
	{
		return ExecFunc(s_FindStringInArrayFunc, arr, item);
	}

	/**
	 * @brief Returns the index for the first occurrence of the provided value. If the value
	 * cannot be located, -1 will be returned.
	 *
	 * @param array         Array Handle.
	 * @param item          Value to search for
	 * @param block         Optionally which block to search in
	 * @return              Array index, or -1 on failure
	 * @error               Invalid Handle or invalid block
	 */
	template<typename any>
	static int FindValueInArray(Handle arr, any item, int block = 0)
	{
		return ExecFunc(s_FindValueInArrayFunc, arr, item, block);
	}

	/**
	 * Returns the blocksize the array was created with.
	 *
	 * @param array         Array Handle.
	 * @return              The blocksize of the array.
	 * @error               Invalid Handle
	 */
	static int GetArrayBlockSize(Handle arr)
	{
		return ExecFunc(s_GetArrayBlockSizeFunc, arr);
	}
