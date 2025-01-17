tsize_t t2p_write_pdf_header(T2P* t2p, TIFF* output){

	tsize_t written=0;
	char buffer[16];
	int buflen=0;
	
	buflen = snprintf(buffer, sizeof(buffer), "%%PDF-%u.%u ",
			  t2p->pdf_majorversion&0xff,
			  t2p->pdf_minorversion&0xff);
	check_snprintf_ret(t2p, buflen, buffer);
	written += t2pWriteFile(output, (tdata_t) buffer, buflen);
	written += t2pWriteFile(output, (tdata_t)"\n%\342\343\317\323\n", 7);

	return(written);
}
