PHP_RSHUTDOWN_FUNCTION(phar) /* {{{ */
{
	int i;

	PHAR_G(request_ends) = 1;

	if (PHAR_G(request_init))
	{
		phar_release_functions();
		zend_hash_destroy(&(PHAR_G(phar_alias_map)));
		PHAR_G(phar_alias_map.u.flags) = 0;
		zend_hash_destroy(&(PHAR_G(phar_fname_map)));
		PHAR_G(phar_fname_map.u.flags) = 0;
		zend_hash_destroy(&(PHAR_G(phar_persist_map)));
		PHAR_G(phar_persist_map.u.flags) = 0;
		PHAR_G(phar_SERVER_mung_list) = 0;

		if (PHAR_G(cached_fp)) {
			for (i = 0; i < zend_hash_num_elements(&cached_phars); ++i) {
				if (PHAR_G(cached_fp)[i].fp) {
					php_stream_close(PHAR_G(cached_fp)[i].fp);
				}
				if (PHAR_G(cached_fp)[i].ufp) {
					php_stream_close(PHAR_G(cached_fp)[i].ufp);
				}
				efree(PHAR_G(cached_fp)[i].manifest);
			}
			efree(PHAR_G(cached_fp));
			PHAR_G(cached_fp) = 0;
		}

		PHAR_G(request_init) = 0;

		if (PHAR_G(cwd)) {
			efree(PHAR_G(cwd));
		}

		PHAR_G(cwd) = NULL;
		PHAR_G(cwd_len) = 0;
		PHAR_G(cwd_init) = 0;
	}

	PHAR_G(request_done) = 1;
	return SUCCESS;
}
/* }}} */
