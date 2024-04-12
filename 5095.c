ZEND_API void * __zend_realloc(void *p, size_t len)
{
	p = realloc(p, len);
	if (EXPECTED(p)) {
		return p;
	}
	zend_out_of_memory();
}
