int phar_detect_phar_fname_ext(const char *filename, int filename_len, const char **ext_str, int *ext_len, int executable, int for_create, int is_complete TSRMLS_DC) /* {{{ */
{
	const char *pos, *slash;

	*ext_str = NULL;
	*ext_len = 0;

	if (!filename_len || filename_len == 1) {
		return FAILURE;
	}

	phar_request_initialize(TSRMLS_C);
	/* first check for alias in first segment */
	pos = memchr(filename, '/', filename_len);

	if (pos && pos != filename) {
		/* check for url like http:// or phar:// */
		if (*(pos - 1) == ':' && (pos - filename) < filename_len - 1 && *(pos + 1) == '/') {
			*ext_len = -2;
			*ext_str = NULL;
			return FAILURE;
		}
		if (zend_hash_exists(&(PHAR_GLOBALS->phar_alias_map), (char *) filename, pos - filename)) {
			*ext_str = pos;
			*ext_len = -1;
			return FAILURE;
		}

		if (PHAR_G(manifest_cached) && zend_hash_exists(&cached_alias, (char *) filename, pos - filename)) {
			*ext_str = pos;
			*ext_len = -1;
			return FAILURE;
		}
	}

	if (zend_hash_num_elements(&(PHAR_GLOBALS->phar_fname_map)) || PHAR_G(manifest_cached)) {
		phar_archive_data **pphar;

		if (is_complete) {
			if (SUCCESS == zend_hash_find(&(PHAR_GLOBALS->phar_fname_map), (char *) filename, filename_len, (void **)&pphar)) {
				*ext_str = filename + (filename_len - (*pphar)->ext_len);
woohoo:
				*ext_len = (*pphar)->ext_len;

				if (executable == 2) {
					return SUCCESS;
				}

				if (executable == 1 && !(*pphar)->is_data) {
					return SUCCESS;
				}

				if (!executable && (*pphar)->is_data) {
					return SUCCESS;
				}

				return FAILURE;
			}

			if (PHAR_G(manifest_cached) && SUCCESS == zend_hash_find(&cached_phars, (char *) filename, filename_len, (void **)&pphar)) {
				*ext_str = filename + (filename_len - (*pphar)->ext_len);
				goto woohoo;
			}
		} else {
			phar_zstr key;
			char *str_key;
			uint keylen;
			ulong unused;

			zend_hash_internal_pointer_reset(&(PHAR_GLOBALS->phar_fname_map));

			while (FAILURE != zend_hash_has_more_elements(&(PHAR_GLOBALS->phar_fname_map))) {
				if (HASH_KEY_NON_EXISTANT == zend_hash_get_current_key_ex(&(PHAR_GLOBALS->phar_fname_map), &key, &keylen, &unused, 0, NULL)) {
					break;
				}

				PHAR_STR(key, str_key);

				if (keylen > (uint) filename_len) {
					zend_hash_move_forward(&(PHAR_GLOBALS->phar_fname_map));
					PHAR_STR_FREE(str_key);
					continue;
				}

				if (!memcmp(filename, str_key, keylen) && ((uint)filename_len == keylen
					|| filename[keylen] == '/' || filename[keylen] == '\0')) {
					PHAR_STR_FREE(str_key);
					if (FAILURE == zend_hash_get_current_data(&(PHAR_GLOBALS->phar_fname_map), (void **) &pphar)) {
						break;
					}
					*ext_str = filename + (keylen - (*pphar)->ext_len);
					goto woohoo;
				}

				PHAR_STR_FREE(str_key);
				zend_hash_move_forward(&(PHAR_GLOBALS->phar_fname_map));
			}

			if (PHAR_G(manifest_cached)) {
				zend_hash_internal_pointer_reset(&cached_phars);

				while (FAILURE != zend_hash_has_more_elements(&cached_phars)) {
					if (HASH_KEY_NON_EXISTANT == zend_hash_get_current_key_ex(&cached_phars, &key, &keylen, &unused, 0, NULL)) {
						break;
					}

					PHAR_STR(key, str_key);

					if (keylen > (uint) filename_len) {
						zend_hash_move_forward(&cached_phars);
						PHAR_STR_FREE(str_key);
						continue;
					}

					if (!memcmp(filename, str_key, keylen) && ((uint)filename_len == keylen
						|| filename[keylen] == '/' || filename[keylen] == '\0')) {
						PHAR_STR_FREE(str_key);
						if (FAILURE == zend_hash_get_current_data(&cached_phars, (void **) &pphar)) {
							break;
						}
						*ext_str = filename + (keylen - (*pphar)->ext_len);
						goto woohoo;
					}
					PHAR_STR_FREE(str_key);
					zend_hash_move_forward(&cached_phars);
				}
			}
		}
	}

	pos = memchr(filename + 1, '.', filename_len);
next_extension:
	if (!pos) {
		return FAILURE;
	}

	while (pos != filename && (*(pos - 1) == '/' || *(pos - 1) == '\0')) {
		pos = memchr(pos + 1, '.', filename_len - (pos - filename) + 1);
		if (!pos) {
			return FAILURE;
		}
	}

	slash = memchr(pos, '/', filename_len - (pos - filename));

	if (!slash) {
		/* this is a url like "phar://blah.phar" with no directory */
		*ext_str = pos;
		*ext_len = strlen(pos);

		/* file extension must contain "phar" */
		switch (phar_check_str(filename, *ext_str, *ext_len, executable, for_create TSRMLS_CC)) {
			case SUCCESS:
				return SUCCESS;
			case FAILURE:
				/* we are at the end of the string, so we fail */
				return FAILURE;
		}
	}

	/* we've found an extension that ends at a directory separator */
	*ext_str = pos;
	*ext_len = slash - pos;

	switch (phar_check_str(filename, *ext_str, *ext_len, executable, for_create TSRMLS_CC)) {
		case SUCCESS:
			return SUCCESS;
		case FAILURE:
			/* look for more extensions */
			pos = strchr(pos + 1, '.');
			if (pos) {
				*ext_str = NULL;
				*ext_len = 0;
			}
			goto next_extension;
	}

	return FAILURE;
}
/* }}} */
