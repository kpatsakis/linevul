tsize_t t2p_write_pdf_obj_start(uint32 number, TIFF* output){

	tsize_t written=0;
	char buffer[32];
	int buflen=0;

	buflen=snprintf(buffer, sizeof(buffer), "%lu", (unsigned long)number);
	check_snprintf_ret((T2P*)NULL, buflen, buffer);
	written += t2pWriteFile(output, (tdata_t) buffer, buflen );
	written += t2pWriteFile(output, (tdata_t) " 0 obj\n", 7);

	return(written);
}
