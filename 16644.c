PHP_MSHUTDOWN_FUNCTION(gd)
{
	T1_CloseLib();
#if HAVE_GD_BUNDLED && HAVE_LIBFREETYPE
	gdFontCacheMutexShutdown();
#endif
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}
