IW_IMPL(void) iw_snprintf(char *buf, size_t buflen, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	iw_vsnprintf(buf,buflen,fmt,ap);
	va_end(ap);
}
