i2flac24_array (const int *src, int32_t *dest, int count)
{	while (--count >= 0)
		dest [count] = src [count] >> 8 ;
} /* i2flac24_array */
