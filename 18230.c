ImportTIFF_DSDTable ( const TIFF_Manager & tiff, const TIFF_Manager::TagInfo & tagInfo,
					  SXMPMeta * xmp, const char * xmpNS, const char * xmpProp )
{
	try {	// Don't let errors with one stop the others.

		const XMP_Uns8 * bytePtr = (XMP_Uns8*)tagInfo.dataPtr;
		const XMP_Uns8 * byteEnd = bytePtr + tagInfo.dataLen;

		XMP_Uns16 columns = *((XMP_Uns16*)bytePtr);
		XMP_Uns16 rows    = *((XMP_Uns16*)(bytePtr+2));
		if ( ! tiff.IsNativeEndian() ) {
			columns = Flip2 ( columns );
			rows = Flip2 ( rows );
		}

		char buffer[20];

		snprintf ( buffer, sizeof(buffer), "%d", columns );	// AUDIT: Use of sizeof(buffer) is safe.
		xmp->SetStructField ( xmpNS, xmpProp, kXMP_NS_EXIF, "Columns", buffer );
		snprintf ( buffer, sizeof(buffer), "%d", rows );	// AUDIT: Use of sizeof(buffer) is safe.
		xmp->SetStructField ( xmpNS, xmpProp, kXMP_NS_EXIF, "Rows", buffer );

		std::string arrayPath;
		SXMPUtils::ComposeStructFieldPath ( xmpNS, xmpProp, kXMP_NS_EXIF, "Settings", &arrayPath );

		bytePtr += 4;	// Move to the list of settings.
		UTF16Unit * utf16Ptr = (UTF16Unit*)bytePtr;
		UTF16Unit * utf16End = (UTF16Unit*)byteEnd;

		std::string utf8;


		while ( utf16Ptr < utf16End ) {

			size_t nameLen = 0;
			while ( utf16Ptr[nameLen] != 0 ) ++nameLen;
			++nameLen;	// ! Include the terminating nul.
			if ( (utf16Ptr + nameLen) > utf16End ) goto BadExif;

			try {
				FromUTF16 ( utf16Ptr, nameLen, &utf8, tiff.IsBigEndian() );
			} catch ( ... ) {
				goto BadExif; // Ignore the tag if there are conversion errors.
			}

			xmp->AppendArrayItem ( xmpNS, arrayPath.c_str(), kXMP_PropArrayIsOrdered, utf8.c_str() );

			utf16Ptr += nameLen;

		}

		return;

	BadExif:	// Ignore the tag if the table is ill-formed.
		xmp->DeleteProperty ( xmpNS, xmpProp );
		return;

	} catch ( ... ) {
	}

}	// ImportTIFF_DSDTable
