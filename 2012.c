static void alloc_globals_dtor(zend_alloc_globals *alloc_globals)
{
	zend_mm_shutdown(alloc_globals->mm_heap, 1, 1);
}
