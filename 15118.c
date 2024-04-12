static unsigned char constant_time_eq_8(unsigned char a, unsigned char b)
	{
	unsigned c = a ^ b;
	c--;
	return DUPLICATE_MSB_TO_ALL_8(c);
	}
