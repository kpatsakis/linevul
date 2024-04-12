PHP_RSHUTDOWN_FUNCTION(phar) /* {{{ */
{
	int i;

	PHAR_GLOBALS->request_ends = 1;

	if (PHAR_GLOBALS->request_init)
	{
		phar_release_functions(TSRMLS_C);
		zend_hash_destroy(&(PHAR_GLOBALS->phar_alias_map));
		PHAR_GLOBALS->phar_alias_map.arBuckets = NULL;
		zend_hash_destroy(&(PHAR_GLOBALS->phar_fname_map));
		PHAR_GLOBALS->phar_fname_map.arBuckets = NULL;
		zend_hash_destroy(&(PHAR_GLOBALS->phar_persist_map));
		PHAR_GLOBALS->phar_persist_map.arBuckets = NULL;
		PHAR_GLOBALS->phar_SERVER_mung_list = 0;

		if (PHAR_GLOBALS->cached_fp) {
			for (i = 0; i < zend_hash_num_elements(&cached_phars); ++i) {
				if (PHAR_GLOBALS->cached_fp[i].fp) {
					php_stream_close(PHAR_GLOBALS->cached_fp[i].fp);
				}
				if (PHAR_GLOBALS->cached_fp[i].ufp) {
					php_stream_close(PHAR_GLOBALS->cached_fp[i].ufp);
				}
				efree(PHAR_GLOBALS->cached_fp[i].manifest);
			}
			efree(PHAR_GLOBALS->cached_fp);
			PHAR_GLOBALS->cached_fp = 0;
		}

		PHAR_GLOBALS->request_init = 0;

		if (PHAR_G(cwd)) {
			efree(PHAR_G(cwd));
		}

		PHAR_G(cwd) = NULL;
		PHAR_G(cwd_len) = 0;
		PHAR_G(cwd_init) = 0;
	}

	PHAR_GLOBALS->request_done = 1;
	return SUCCESS;
}
/* }}} */
