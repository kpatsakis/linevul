PHP_RSHUTDOWN_FUNCTION(gd)
{
#if HAVE_GD_FONTCACHESHUTDOWN
	gdFontCacheShutdown();
#else
	gdFreeFontCache();
#endif
	return SUCCESS;
}
