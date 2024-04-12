IW_IMPL(void) iw_vsnprintf(char *buf, size_t buflen, const char *fmt, va_list ap)
{
#ifdef IW_WINDOWS
	StringCchVPrintfA(buf,buflen,fmt,ap);
#else
	vsnprintf(buf,buflen,fmt,ap);
	buf[buflen-1]='\0';
#endif
}
