void TIFF_MetaHandler::ProcessXMP()
{

this->processedXMP = true;	// Make sure we only come through here once.

// Set up everything for the legacy import, but don't do it yet. This lets us do a forced legacy
// import if the XMP packet gets parsing errors.

// ! Photoshop 6 wrote annoyingly wacky TIFF files. It buried a lot of the Exif metadata inside
// ! image resource 1058, itself inside of tag 34377 in the 0th IFD. Take care of this before
// ! doing any of the legacy metadata presence or priority analysis. Delete image resource 1058
// ! to get rid of the buried Exif, but don't mark the XMPFiles object as changed. This change
// ! should not trigger an update, but should be included as part of a normal update.

bool found;
bool readOnly = ((this->parent->openFlags & kXMPFiles_OpenForUpdate) == 0);

if ( readOnly ) {
this->psirMgr = new PSIR_MemoryReader();
this->iptcMgr = new IPTC_Reader();
} else {
this->psirMgr = new PSIR_FileWriter();
this->iptcMgr = new IPTC_Writer();	// ! Parse it later.
}

TIFF_Manager & tiff = this->tiffMgr;	// Give the compiler help in recognizing non-aliases.
PSIR_Manager & psir = *this->psirMgr;
IPTC_Manager & iptc = *this->iptcMgr;

TIFF_Manager::TagInfo psirInfo;
bool havePSIR = tiff.GetTag ( kTIFF_PrimaryIFD, kTIFF_PSIR, &psirInfo );

if ( havePSIR ) {	// ! Do the Photoshop 6 integration before other legacy analysis.
psir.ParseMemoryResources ( psirInfo.dataPtr, psirInfo.dataLen );
PSIR_Manager::ImgRsrcInfo buriedExif;
found = psir.GetImgRsrc ( kPSIR_Exif, &buriedExif );
if ( found ) {
tiff.IntegrateFromPShop6 ( buriedExif.dataPtr, buriedExif.dataLen );
if ( ! readOnly ) psir.DeleteImgRsrc ( kPSIR_Exif );
}
}

TIFF_Manager::TagInfo iptcInfo;
bool haveIPTC = tiff.GetTag ( kTIFF_PrimaryIFD, kTIFF_IPTC, &iptcInfo );	// The TIFF IPTC tag.
int iptcDigestState = kDigestMatches;

if ( haveIPTC ) {

bool haveDigest = false;
PSIR_Manager::ImgRsrcInfo digestInfo;
if ( havePSIR ) haveDigest = psir.GetImgRsrc ( kPSIR_IPTCDigest, &digestInfo );
if ( digestInfo.dataLen != 16 ) haveDigest = false;

if ( ! haveDigest ) {

iptcDigestState = kDigestMissing;

} else {

// Older versions of Photoshop wrote tag 33723 with type LONG, but ignored the trailing
// zero padding for the IPTC digest. If the full digest differs, recheck without the padding.

iptcDigestState = PhotoDataUtils::CheckIPTCDigest ( iptcInfo.dataPtr, iptcInfo.dataLen, digestInfo.dataPtr );
			if ( (iptcDigestState == kDigestDiffers) && (kTIFF_TypeSizes[iptcInfo.type] > 1) ) {
XMP_Uns8 * endPtr = (XMP_Uns8*)iptcInfo.dataPtr + iptcInfo.dataLen - 1;
XMP_Uns8 * minPtr = endPtr - kTIFF_TypeSizes[iptcInfo.type] + 1;
while ( (endPtr >= minPtr) && (*endPtr == 0) ) --endPtr;
iptcDigestState = PhotoDataUtils::CheckIPTCDigest ( iptcInfo.dataPtr, unpaddedLen, digestInfo.dataPtr );
}

}

}

XMP_OptionBits options = k2XMP_FileHadExif;	// TIFF files are presumed to have Exif legacy.
if ( haveIPTC ) options |= k2XMP_FileHadIPTC;
if ( this->containsXMP ) options |= k2XMP_FileHadXMP;

// Process the XMP packet. If it fails to parse, do a forced legacy import but still throw an
// exception. This tells the caller that an error happened, but gives them recovered legacy
// should they want to proceed with that.

bool haveXMP = false;

if ( ! this->xmpPacket.empty() ) {
XMP_Assert ( this->containsXMP );
// Common code takes care of packetInfo.charForm, .padSize, and .writeable.
XMP_StringPtr packetStr = this->xmpPacket.c_str();
XMP_StringLen packetLen = (XMP_StringLen)this->xmpPacket.size();
try {
this->xmpObj.ParseFromBuffer ( packetStr, packetLen );
} catch ( ... ) { /* Ignore parsing failures, someday we hope to get partial XMP back. */ }
haveXMP = true;
}

// Process the legacy metadata.

if ( haveIPTC && (! haveXMP) && (iptcDigestState == kDigestMatches) ) iptcDigestState = kDigestMissing;
bool parseIPTC = (iptcDigestState != kDigestMatches) || (! readOnly);
if ( parseIPTC ) iptc.ParseMemoryDataSets ( iptcInfo.dataPtr, iptcInfo.dataLen );
ImportPhotoData ( tiff, iptc, psir, iptcDigestState, &this->xmpObj, options );

this->containsXMP = true;	// Assume we now have something in the XMP.

}	// TIFF_MetaHandler::ProcessXMP
