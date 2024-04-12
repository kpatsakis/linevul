count_leap(int y)
{
	return (y - 1969) / 4 - (y - 1901) / 100 + (y - 1601) / 400;
}
