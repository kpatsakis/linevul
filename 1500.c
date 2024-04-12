IW_IMPL(const char*) iw_get_fmt_name(int fmt)
{
	static const char *n;
	n=NULL;
	switch(fmt) {
	case IW_FORMAT_PNG:  n="PNG";  break;
	case IW_FORMAT_JPEG: n="JPEG"; break;
	case IW_FORMAT_BMP:  n="BMP";  break;
	case IW_FORMAT_TIFF: n="TIFF"; break;
	case IW_FORMAT_MIFF: n="MIFF"; break;
	case IW_FORMAT_WEBP: n="WebP"; break;
	case IW_FORMAT_GIF:  n="GIF";  break;
	case IW_FORMAT_PNM:  n="PNM";  break;
	case IW_FORMAT_PBM:  n="PBM";  break;
	case IW_FORMAT_PGM:  n="PGM";  break;
	case IW_FORMAT_PPM:  n="PPM";  break;
	case IW_FORMAT_PAM:  n="PAM";  break;
	}
	return n;
}
