bool PhotoDataUtils::GetNativeInfo ( const TIFF_Manager & exif, XMP_Uns8 ifd, XMP_Uns16 id, TIFF_Manager::TagInfo * info )
{
	bool haveExif = exif.GetTag ( ifd, id, info );

	if ( haveExif ) {

		XMP_Uns32 i;
		char * chPtr;
		
		XMP_Assert ( (info->dataPtr != 0) || (info->dataLen == 0) );	// Null pointer requires zero length.

		bool isDate = ((id == kTIFF_DateTime) || (id == kTIFF_DateTimeOriginal) || (id == kTIFF_DateTimeOriginal));

		for ( i = 0, chPtr = (char*)info->dataPtr; i < info->dataLen; ++i, ++chPtr ) {
			if ( isDate && (*chPtr == ':') ) continue;	// Ignore colons, empty dates have spaces and colons.
			if ( (*chPtr != ' ') && (*chPtr != 0) ) break;	// Break if the Exif value is non-empty.
		}

		if ( i == info->dataLen ) {
			haveExif = false;	// Ignore empty Exif.
		} else {
			TrimTrailingSpaces ( info );
			if ( info->dataLen == 0 ) haveExif = false;
		}

	}

	return haveExif;

}	// PhotoDataUtils::GetNativeInfo
