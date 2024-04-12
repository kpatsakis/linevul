ImportTIFF_StandardMappings ( XMP_Uns8 ifd, const TIFF_Manager & tiff, SXMPMeta * xmp )
{
	const bool nativeEndian = tiff.IsNativeEndian();
	TIFF_Manager::TagInfo tagInfo;

	const TIFF_MappingToXMP * mappings = 0;

	if ( ifd == kTIFF_PrimaryIFD ) {
		mappings = sPrimaryIFDMappings;
	} else if ( ifd == kTIFF_ExifIFD ) {
		mappings = sExifIFDMappings;
	} else if ( ifd == kTIFF_GPSInfoIFD ) {
		mappings = sGPSInfoIFDMappings;
	} else {
		XMP_Throw ( "Invalid IFD for standard mappings", kXMPErr_InternalFailure );
	}

	for ( size_t i = 0; mappings[i].id != 0xFFFF; ++i ) {

		try {	// Don't let errors with one stop the others.

			const TIFF_MappingToXMP & mapInfo =  mappings[i];
			const bool mapSingle = ((mapInfo.count == 1) || (mapInfo.type == kTIFF_ASCIIType));

			if ( mapInfo.name[0] == 0 ) continue;	// Skip special mappings, handled higher up.
			
			bool found = tiff.GetTag ( ifd, mapInfo.id, &tagInfo );
			if ( ! found ) continue;

			XMP_Assert ( tagInfo.type != kTIFF_UndefinedType );	// These must have a special mapping.
			if ( tagInfo.type == kTIFF_UndefinedType ) continue;
			if ( ! ImportTIFF_CheckStandardMapping ( tagInfo, mapInfo ) ) continue;

			if ( mapSingle ) {
				ImportSingleTIFF ( tagInfo, nativeEndian, xmp, mapInfo.ns, mapInfo.name );
			} else {
				ImportArrayTIFF ( tagInfo, nativeEndian, xmp, mapInfo.ns, mapInfo.name );
			}

		} catch ( ... ) {


		}

	}

}	// ImportTIFF_StandardMappings
