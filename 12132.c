_PUBLIC_ int strcasecmp_m(const char *s1, const char *s2)
{
	struct smb_iconv_handle *iconv_handle = get_iconv_handle();
	return strcasecmp_m_handle(iconv_handle, s1, s2);
}
