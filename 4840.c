GahpClient::getErrorString()
{
	static std::string output;

	output = "";

	unsigned int i = 0;
	unsigned int input_len = error_string.length();
	for (i=0; i < input_len; i++) {
		switch (error_string[i]) {
		case '\n':
			output += "\\n";
			break;
		case '\r':
			output += "\\r";
			break;
		default:
			output += error_string[i];
			break;
		}
	}

	return output.c_str();
}
