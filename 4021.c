ZEND_MM_BINS_INFO(_ZEND_BIN_ALLOCATOR, x, y)

ZEND_API void* ZEND_FASTCALL _emalloc_large(size_t size ZEND_FILE_LINE_DC ZEND_FILE_LINE_ORIG_DC)
{

	ZEND_MM_CUSTOM_ALLOCATOR(size);
	return zend_mm_alloc_large(AG(mm_heap), size ZEND_FILE_LINE_RELAY_CC ZEND_FILE_LINE_ORIG_RELAY_CC);
}
