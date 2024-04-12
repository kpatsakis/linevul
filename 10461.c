IW_IMPL(int) iw_parse_number_list(const char *s,
	int max_numbers, // max number of numbers to parse
	double *results) // array of doubles to hold the results
{
	int n;
	int charsread;
	int curpos=0;
	int ret;
	int numresults = 0;

	for(n=0;n<max_numbers;n++) {
		ret=iw_parse_number_internal(&s[curpos], &results[n], &charsread);
		if(!ret) break;
		numresults++;
		curpos+=charsread;
		if(s[curpos]==',') {
			curpos++;
		}
		else {
			break;
		}
	}
	return numresults;
}
