static bool push_int_bigendian(struct asn1_data *data, unsigned int i, bool negative)
{
	uint8_t lowest = i & 0xFF;

	i = i >> 8;
	if (i != 0)
		if (!push_int_bigendian(data, i, negative))
			return false;

	if (data->nesting->start+1 == data->ofs) {

		/* We did not write anything yet, looking at the highest
		 * valued byte */

		if (negative) {
			/* Don't write leading 0xff's */
			if (lowest == 0xFF)
				return true;

			if ((lowest & 0x80) == 0) {
				/* The only exception for a leading 0xff is if
				 * the highest bit is 0, which would indicate
				 * a positive value */
				if (!asn1_write_uint8(data, 0xff))
					return false;
			}
		} else {
			if (lowest & 0x80) {
				/* The highest bit of a positive integer is 1,
				 * this would indicate a negative number. Push
				 * a 0 to indicate a positive one */
				if (!asn1_write_uint8(data, 0))
					return false;
			}
		}
	}

	return asn1_write_uint8(data, lowest);
}
