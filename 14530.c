IW_IMPL(double) iw_parse_number(const char *s)
{
	double result;
	int charsread;
	iw_parse_number_internal(s, &result, &charsread);
	return result;
}
