PixarLogPreDecode(TIFF* tif, uint16 s)
{
	static const char module[] = "PixarLogPreDecode";
	PixarLogState* sp = DecoderState(tif);

	(void) s;
	assert(sp != NULL);
	sp->stream.next_in = tif->tif_rawdata;
	assert(sizeof(sp->stream.avail_in)==4);  /* if this assert gets raised,
	    we need to simplify this code to reflect a ZLib that is likely updated
	    to deal with 8byte memory sizes, though this code will respond
	    appropriately even before we simplify it */
	sp->stream.avail_in = (uInt) tif->tif_rawcc;
	if ((tmsize_t)sp->stream.avail_in != tif->tif_rawcc)
	{
		TIFFErrorExt(tif->tif_clientdata, module, "ZLib cannot deal with buffers this size");
		return (0);
	}
	return (inflateReset(&sp->stream) == Z_OK);
}
