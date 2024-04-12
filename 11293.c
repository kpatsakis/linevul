void* iwpvt_default_malloc(void *userdata, unsigned int flags, size_t n)
{
	if(flags & IW_MALLOCFLAG_ZEROMEM) {
		return calloc(n,1);
	}
	return malloc(n);
}
