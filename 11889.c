TIFFInitPixarLog(TIFF* tif, int scheme)
{
	static const char module[] = "TIFFInitPixarLog";

	PixarLogState* sp;

	assert(scheme == COMPRESSION_PIXARLOG);

	/*
	 * Merge codec-specific tag information.
	 */
	if (!_TIFFMergeFields(tif, pixarlogFields,
			      TIFFArrayCount(pixarlogFields))) {
		TIFFErrorExt(tif->tif_clientdata, module,
			     "Merging PixarLog codec-specific tags failed");
		return 0;
	}

	/*
	 * Allocate state block so tag methods have storage to record values.
	 */
	tif->tif_data = (uint8*) _TIFFmalloc(sizeof (PixarLogState));
	if (tif->tif_data == NULL)
		goto bad;
	sp = (PixarLogState*) tif->tif_data;
	_TIFFmemset(sp, 0, sizeof (*sp));
	sp->stream.data_type = Z_BINARY;
	sp->user_datafmt = PIXARLOGDATAFMT_UNKNOWN;

	/*
	 * Install codec methods.
	 */
	tif->tif_fixuptags = PixarLogFixupTags; 
	tif->tif_setupdecode = PixarLogSetupDecode;
	tif->tif_predecode = PixarLogPreDecode;
	tif->tif_decoderow = PixarLogDecode;
	tif->tif_decodestrip = PixarLogDecode;  
	tif->tif_decodetile = PixarLogDecode;
	tif->tif_setupencode = PixarLogSetupEncode;
	tif->tif_preencode = PixarLogPreEncode;
	tif->tif_postencode = PixarLogPostEncode;
	tif->tif_encoderow = PixarLogEncode;  
	tif->tif_encodestrip = PixarLogEncode;
	tif->tif_encodetile = PixarLogEncode;  
	tif->tif_close = PixarLogClose;
	tif->tif_cleanup = PixarLogCleanup;

	/* Override SetField so we can handle our private pseudo-tag */
	sp->vgetparent = tif->tif_tagmethods.vgetfield;
	tif->tif_tagmethods.vgetfield = PixarLogVGetField;   /* hook for codec tags */
	sp->vsetparent = tif->tif_tagmethods.vsetfield;
	tif->tif_tagmethods.vsetfield = PixarLogVSetField;   /* hook for codec tags */

	/* Default values for codec-specific fields */
	sp->quality = Z_DEFAULT_COMPRESSION; /* default comp. level */
	sp->state = 0;

	/* we don't wish to use the predictor, 
	 * the default is none, which predictor value 1
	 */
	(void) TIFFPredictorInit(tif);

	/*
	 * build the companding tables 
	 */
	PixarLogMakeTables(sp);

	return (1);
bad:
	TIFFErrorExt(tif->tif_clientdata, module,
		     "No space for PixarLog state block");
	return (0);
}
