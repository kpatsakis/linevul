Condor_Auth_SSL::unwrap(char *   input, 
						   int      input_len, 
						   char*&   output, 
						   int&     output_len)
{
	bool result;
	unsigned char* in = (unsigned char*)input;
	unsigned char* out = (unsigned char*)output;
	
	dprintf(D_SECURITY, "In unwrap.\n");
	result = decrypt(in,input_len,out,output_len);
	
	output = (char *)out;
	
	return result ? TRUE : FALSE;
}
