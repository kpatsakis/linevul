static int entersafe_process_fci(struct sc_card *card, struct sc_file *file,
						  const u8 *buf, size_t buflen)
{
	 int r;

	 assert(file);
	 SC_FUNC_CALLED(card->ctx, SC_LOG_DEBUG_VERBOSE);

	 r = iso_ops->process_fci(card,file,buf,buflen);
	 SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "Process fci failed");

	 if(file->namelen)
	 {
		  file->type = SC_FILE_TYPE_DF;
		  file->ef_structure = SC_FILE_EF_UNKNOWN;
	 }
	 else
	 {
		  file->type = SC_FILE_TYPE_WORKING_EF;
		  file->ef_structure = SC_FILE_EF_TRANSPARENT;
	 }

	 SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_VERBOSE, r);
}
