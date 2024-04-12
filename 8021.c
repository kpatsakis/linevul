escapeGahpString(const char * input) 
{
	static std::string output;

	if (!input) return NULL;

	output = "";

	unsigned int i = 0;
	size_t input_len = strlen(input);
	for (i=0; i < input_len; i++) {
		if ( input[i] == ' ' || input[i] == '\\' || input[i] == '\r' ||
			 input[i] == '\n' ) {
			output += '\\';
		}
		output += input[i];
	}

	return output.c_str();
}
