ImportArrayTIFF_Short ( const TIFF_Manager::TagInfo & tagInfo, const bool nativeEndian,
						SXMPMeta * xmp, const char * xmpNS, const char * xmpProp )
{
	try {	// Don't let errors with one stop the others.

		XMP_Uns16 * binPtr = (XMP_Uns16*)tagInfo.dataPtr;
		
		xmp->DeleteProperty ( xmpNS, xmpProp );	// ! Don't keep appending, create a new array.

		for ( size_t i = 0; i < tagInfo.count; ++i, ++binPtr ) {

			XMP_Uns16 binValue = *binPtr;
			if ( ! nativeEndian ) binValue = Flip2 ( binValue );

			char strValue[20];
			snprintf ( strValue, sizeof(strValue), "%hu", binValue );	// AUDIT: Using sizeof(strValue) is safe.

			xmp->AppendArrayItem ( xmpNS, xmpProp, kXMP_PropArrayIsOrdered, strValue );

		}

	} catch ( ... ) {
	}

}	// ImportArrayTIFF_Short
