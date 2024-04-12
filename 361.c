void phar_destroy_phar_data(phar_archive_data *phar) /* {{{ */
{
	if (phar->alias && phar->alias != phar->fname) {
		pefree(phar->alias, phar->is_persistent);
		phar->alias = NULL;
	}

	if (phar->fname) {
		pefree(phar->fname, phar->is_persistent);
		phar->fname = NULL;
	}

	if (phar->signature) {
		pefree(phar->signature, phar->is_persistent);
		phar->signature = NULL;
	}

	if (phar->manifest.u.flags) {
		zend_hash_destroy(&phar->manifest);
		phar->manifest.u.flags = 0;
	}

	if (phar->mounted_dirs.u.flags) {
		zend_hash_destroy(&phar->mounted_dirs);
		phar->mounted_dirs.u.flags = 0;
	}

	if (phar->virtual_dirs.u.flags) {
		zend_hash_destroy(&phar->virtual_dirs);
		phar->virtual_dirs.u.flags = 0;
	}

	if (Z_TYPE(phar->metadata) != IS_UNDEF) {
		if (phar->is_persistent) {
			if (phar->metadata_len) {
				/* for zip comments that are strings */
				free(Z_PTR(phar->metadata));
			} else {
				zval_internal_ptr_dtor(&phar->metadata);
			}
		} else {
			zval_ptr_dtor(&phar->metadata);
		}
		phar->metadata_len = 0;
		ZVAL_UNDEF(&phar->metadata);
	}

	if (phar->fp) {
		php_stream_close(phar->fp);
		phar->fp = 0;
	}

	if (phar->ufp) {
		php_stream_close(phar->ufp);
		phar->ufp = 0;
	}

	pefree(phar, phar->is_persistent);
}
/* }}}*/
