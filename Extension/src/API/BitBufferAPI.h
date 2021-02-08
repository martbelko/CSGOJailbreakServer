public:
	/**
	 * Writes a single bit to a writable bitbuffer (bf_write).
	 *
	 * @param bf            bf_write handle to write to.
	 * @param bit           Bit to write (true for 1, false for 0).
	 * @error               Invalid or incorrect Handle.
	 */
	static void BfWriteBool(Handle bf, bool bit)
	{
		ExecFunc(s_BfWriteBoolFunc, bf, bit);
	}

	/**
	 * Writes a byte to a writable bitbuffer (bf_write).
	 *
	 * @param bf            bf_write handle to write to.
	 * @param byte          Byte to write (value will be written as 8bit).
	 * @error               Invalid or incorrect Handle.
	 */
	static void BfWriteByte(Handle bf, int byte)
	{
		ExecFunc(s_BfWriteByteFunc, bf, byte);
	}

	/**
	 * Writes a byte to a writable bitbuffer (bf_write).
	 *
	 * @param bf            bf_write handle to write to.
	 * @param chr           Character to write.
	 * @error               Invalid or incorrect Handle.
	 */
	static void BfWriteChar(Handle bf, int chr)
	{
		ExecFunc(s_BfWriteCharFunc, bf, chr);
	}

	/**
	 * Writes a 16bit integer to a writable bitbuffer (bf_write).
	 *
	 * @param bf            bf_write handle to write to.
	 * @param num           Integer to write (value will be written as 16bit).
	 * @error               Invalid or incorrect Handle.
	 */
	static void BfWriteShort(Handle bf, int num)
	{
		ExecFunc(s_BfWriteShortFunc, bf, num);
	}

	/**
	 * Writes a 16bit unsigned integer to a writable bitbuffer (bf_write).
	 *
	 * @param bf            bf_write handle to write to.
	 * @param num           Integer to write (value will be written as 16bit).
	 * @error               Invalid or incorrect Handle.
	 */
	static void BfWriteWord(Handle bf, int num)
	{
		ExecFunc(s_BfWriteWordFunc, bf, num);
	}

	/**
	 * Writes a normal integer to a writable bitbuffer (bf_write).
	 *
	 * @param bf            bf_write handle to write to.
	 * @param num           Integer to write (value will be written as 32bit).
	 * @error               Invalid or incorrect Handle.
	 */
	static void BfWriteNum(Handle bf, int num)
	{
		ExecFunc(s_BfWriteNumFunc, bf, num);
	}

	/**
	 * Writes a floating point number to a writable bitbuffer (bf_write).
	 *
	 * @param bf            bf_write handle to write to.
	 * @param num           Number to write.
	 * @error               Invalid or incorrect Handle.
	 */
	static void BfWriteFloat(Handle bf, float num)
	{
		ExecFunc(s_BfWriteFloatFunc, bf, num);
	}

	/**
	 * Writes a string to a writable bitbuffer (bf_write).
	 *
	 * @param bf            bf_write handle to write to.
	 * @param string        Text string to write.
	 * @error               Invalid or incorrect Handle.
	 */
	static void BfWriteString(Handle bf, const char* string)
	{
		ExecFunc(s_BfWriteStringFunc, bf, string);
	}

	/**
	 * Writes an entity to a writable bitbuffer (bf_write).
	 * @note This is a wrapper around BfWriteShort().
	 *
	 * @param bf            bf_write handle to write to.
	 * @param ent           Entity index to write.
	 * @error               Invalid or incorrect Handle, or invalid entity.
	 */
	static void BfWriteEntity(Handle bf, int ent)
	{
		ExecFunc(s_BfWriteEntityFunc, bf, ent);
	}

	/**
	 * Writes a bit angle to a writable bitbuffer (bf_write).
	 *
	 * @param bf            bf_write handle to write to.
	 * @param angle         Angle to write.
	 * @param numBits       Optional number of bits to use.
	 * @error               Invalid or incorrect Handle.
	 */
	static void BfWriteAngle(Handle bf, float angle, int numBits = 8)
	{
		ExecFunc(s_BfWriteAngleFunc, bf, angle, numBits);
	}

	/**
	 * Writes a coordinate to a writable bitbuffer (bf_write).
	 *
	 * @param bf            bf_write handle to write to.
	 * @param coord         Coordinate to write.
	 * @error               Invalid or incorrect Handle.
	 */
	static void BfWriteCoord(Handle bf, float coord)
	{
		ExecFunc(s_BfWriteCoordFunc, bf, coord);
	}

	/**
	 * Writes a 3D vector of coordinates to a writable bitbuffer (bf_write).
	 *
	 * @param bf            bf_write handle to write to.
	 * @param coord         Coordinate array to write.
	 * @error               Invalid or incorrect Handle.
	 */
	static void BfWriteVecCoord(Handle bf, float coord[3])
	{
		PushArg(s_BfWriteVecCoordFunc, bf);
		PushArg(s_BfWriteVecCoordFunc, coord, 3);
		ExecFunc(s_BfWriteVecCoordFunc);
	}

	/**
	 * Writes a 3D normal vector to a writable bitbuffer (bf_write).
	 *
	 * @param bf            bf_write handle to write to.
	 * @param vec           Vector to write.
	 * @error               Invalid or incorrect Handle.
	 */
	static void BfWriteVecNormal(Handle bf, float vec[3])
	{
		PushArg(s_BfWriteVecNormalFunc, bf);
		PushArg(s_BfWriteVecNormalFunc, vec, 3);
		ExecFunc(s_BfWriteVecNormalFunc);
	}

	/**
	 * Writes a 3D angle vector to a writable bitbuffer (bf_write).
	 *
	 * @param bf            bf_write handle to write to.
	 * @param angles        Angle vector to write.
	 * @error               Invalid or incorrect Handle.
	 */
	static void BfWriteAngles(Handle bf, float angles[3])
	{
		PushArg(s_BfWriteAngleFunc, bf);
		PushArg(s_BfWriteAngleFunc, angles, 3);
		ExecFunc(s_BfWriteAngleFunc);
	}

	/**
	 * Reads a single bit from a readable bitbuffer (bf_read).
	 *
	 * @param bf            bf_read handle to read from.
	 * @return              Bit value read.
	 * @error               Invalid or incorrect Handle.
	 */
	static bool BfReadBool(Handle bf)
	{
		return ExecFunc(s_BfReadBoolFunc, bf);
	}

	/**
	 * Reads a byte from a readable bitbuffer (bf_read).
	 *
	 * @param bf            bf_read handle to read from.
	 * @return              Byte value read (read as 8bit).
	 * @error               Invalid or incorrect Handle.
	 */
	static int BfReadByte(Handle bf)
	{
		return ExecFunc(s_BfReadByteFunc);
	}

	/**
	 * Reads a character from a readable bitbuffer (bf_read).
	 *
	 * @param bf            bf_read handle to read from.
	 * @return              Character value read.
	 * @error               Invalid or incorrect Handle.
	 */
	static int BfReadChar(Handle bf)
	{
		return ExecFunc(s_BfReadCharFunc, bf);
	}

	/**
	 * Reads a 16bit integer from a readable bitbuffer (bf_read).
	 *
	 * @param bf            bf_read handle to read from.
	 * @return              Integer value read (read as 16bit).
	 * @error               Invalid or incorrect Handle.
	 */
	static int BfReadShort(Handle bf)
	{
		return ExecFunc(s_BfReadShortFunc, bf);
	}

	/**
	 * Reads a 16bit unsigned integer from a readable bitbuffer (bf_read).
	 *
	 * @param bf            bf_read handle to read from.
	 * @return              Integer value read (read as 16bit).
	 * @error               Invalid or incorrect Handle.
	 */
	static int BfReadWord(Handle bf)
	{
		return ExecFunc(s_BfReadWordFunc, bf);
	}

	/**
	 * Reads a normal integer to a readable bitbuffer (bf_read).
	 *
	 * @param bf            bf_read handle to read from.
	 * @return              Integer value read (read as 32bit).
	 * @error               Invalid or incorrect Handle.
	 */
	static int BfReadNum(Handle bf)
	{
		return ExecFunc(s_BfReadNumFunc, bf);
	}

	/**
	 * Reads a floating point number from a readable bitbuffer (bf_read).
	 *
	 * @param bf            bf_read handle to read from.
	 * @return              Floating point value read.
	 * @error               Invalid or incorrect Handle.
	 */
	static float BfReadFloat(Handle bf)
	{
		return ExecFunc(s_BfReadFloatFunc, bf);
	}

	/**
	 * Reads a string from a readable bitbuffer (bf_read).
	 *
	 * @param bf            bf_read handle to read from.
	 * @param buffer        Destination string buffer.
	 * @param maxlength     Maximum length of output string buffer.
	 * @param line          If true the buffer will be copied until it reaches a '\n' or a null terminator.
	 * @return              Number of bytes written to the buffer.  If the bitbuffer stream overflowed,
	 *                      that is, had no terminator before the end of the stream, then a negative
	 *                      number will be returned equal to the number of characters written to the
	 *                      buffer minus 1.  The buffer will be null terminated regardless of the
	 *                      return value.
	 * @error               Invalid or incorrect Handle.
	 */
	static int BfReadString(Handle bf, char* buffer, int maxlength, bool line = false)
	{
		PushArg(s_BfReadStringFunc, bf);
		PushArg(s_BfReadStringFunc, buffer, maxlength);
		PushArg(s_BfReadStringFunc, maxlength);
		PushArg(s_BfReadStringFunc, line);
		return ExecFunc(s_BfReadStringFunc);
	}

	/**
	 * Reads an entity from a readable bitbuffer (bf_read).
	 * @note This is a wrapper around BfReadShort().
	 *
	 * @param bf            bf_read handle to read from.
	 * @return              Entity index read.
	 * @error               Invalid or incorrect Handle.
	 */
	static int BfReadEntity(Handle bf)
	{
		return ExecFunc(s_BfReadEntityFunc, bf);
	}

	/**
	 * Reads a bit angle from a readable bitbuffer (bf_read).
	 *
	 * @param bf            bf_read handle to read from.
	 * @param numBits       Optional number of bits to use.
	 * @return              Angle read.
	 * @error               Invalid or incorrect Handle.
	 */
	static float BfReadAngle(Handle bf, int numBits = 8)
	{
		return ExecFunc(s_BfReadAngleFunc, bf, numBits);
	}

	/**
	 * Reads a coordinate from a readable bitbuffer (bf_read).
	 *
	 * @param bf            bf_read handle to read from.
	 * @return              Coordinate read.
	 * @error               Invalid or incorrect Handle.
	 */
	static float BfReadCoord(Handle bf)
	{
		return ExecFunc(s_BfReadCoordFunc, bf);
	}

	/**
	 * Reads a 3D vector of coordinates from a readable bitbuffer (bf_read).
	 *
	 * @param bf            bf_read handle to read from.
	 * @param coord         Destination coordinate array.
	 * @error               Invalid or incorrect Handle.
	 */
	static void BfReadVecCoord(Handle bf, float coord[3])
	{
		PushArg(s_BfReadVecCoordFunc, bf);
		PushArg(s_BfReadVecCoordFunc, coord, 3);
		ExecFunc(s_BfReadVecCoordFunc);
	}

	/**
	 * Reads a 3D normal vector from a readable bitbuffer (bf_read).
	 *
	 * @param bf            bf_read handle to read from.
	 * @param vec           Destination vector array.
	 * @error               Invalid or incorrect Handle.
	 */
	static void BfReadVecNormal(Handle bf, float vec[3])
	{
		PushArg(s_BfReadVecNormalFunc, bf);
		PushArg(s_BfReadVecNormalFunc, vec, 3);
		ExecFunc(s_BfReadVecNormalFunc);
	}

	/**
	 * Reads a 3D angle vector from a readable bitbuffer (bf_read).
	 *
	 * @param bf            bf_read handle to read from.
	 * @param angles        Destination angle vector.
	 * @error               Invalid or incorrect Handle.
	 */
	static void BfReadAngles(Handle bf, float angles[3])
	{
		PushArg(s_BfReadAnglesFunc, bf);
		PushArg(s_BfReadAnglesFunc, angles, 3);
		ExecFunc(s_BfReadAnglesFunc);
	}

	/**
	 * Returns the number of bytes left in a readable bitbuffer (bf_read).
	 *
	 * @param bf            bf_read handle to read from.
	 * @return              Number of bytes left unread.
	 * @error               Invalid or incorrect Handle.
	 */
	static int BfGetNumBytesLeft(Handle bf)
	{
		return ExecFunc(s_BfGetNumBytesLeftFunc, bf);
	}
