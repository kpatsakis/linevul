tsize_t t2p_write_pdf_transfer_dict(T2P* t2p, TIFF* output, uint16 i){

	tsize_t written=0;
	char buffer[32];
	int buflen=0;
	(void)i; /* XXX */

	written += t2pWriteFile(output, (tdata_t) "/FunctionType 0 \n", 17);
	written += t2pWriteFile(output, (tdata_t) "/Domain [0.0 1.0] \n", 19);
	written += t2pWriteFile(output, (tdata_t) "/Range [0.0 1.0] \n", 18);
	buflen=snprintf(buffer, sizeof(buffer), "/Size [%u] \n", (1<<t2p->tiff_bitspersample));
	check_snprintf_ret(t2p, buflen, buffer);
	written += t2pWriteFile(output, (tdata_t) buffer, buflen);
	written += t2pWriteFile(output, (tdata_t) "/BitsPerSample 16 \n", 19);
	written += t2p_write_pdf_stream_dict(((tsize_t)1)<<(t2p->tiff_bitspersample+1), 0, output);

	return(written);
}
