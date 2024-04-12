int phar_create_or_parse_filename(char *fname, int fname_len, char *alias, int alias_len, int is_data, int options, phar_archive_data** pphar, char **error) /* {{{ */
{
	phar_archive_data *mydata;
	php_stream *fp;
	zend_string *actual = NULL;
	char *p;

	if (!pphar) {
		pphar = &mydata;
	}
#if PHP_API_VERSION < 20100412
	if (PG(safe_mode) && (!php_checkuid(fname, NULL, CHECKUID_ALLOW_ONLY_FILE))) {
		return FAILURE;
	}
#endif
	if (php_check_open_basedir(fname)) {
		return FAILURE;
	}

	/* first open readonly so it won't be created if not present */
	fp = php_stream_open_wrapper(fname, "rb", IGNORE_URL|STREAM_MUST_SEEK|0, &actual);

	if (actual) {
		fname = ZSTR_VAL(actual);
		fname_len = ZSTR_LEN(actual);
	}

	if (fp) {
		if (phar_open_from_fp(fp, fname, fname_len, alias, alias_len, options, pphar, is_data, error) == SUCCESS) {
			if ((*pphar)->is_data || !PHAR_G(readonly)) {
				(*pphar)->is_writeable = 1;
			}
			if (actual) {
				zend_string_release(actual);
			}
			return SUCCESS;
		} else {
			/* file exists, but is either corrupt or not a phar archive */
			if (actual) {
				zend_string_release(actual);
			}
			return FAILURE;
		}
	}

	if (actual) {
		zend_string_release(actual);
	}

	if (PHAR_G(readonly) && !is_data) {
		if (options & REPORT_ERRORS) {
			if (error) {
				spprintf(error, 0, "creating archive \"%s\" disabled by the php.ini setting phar.readonly", fname);
			}
		}
		return FAILURE;
	}

	/* set up our manifest */
	mydata = ecalloc(1, sizeof(phar_archive_data));
	mydata->fname = expand_filepath(fname, NULL);
	fname_len = strlen(mydata->fname);
#ifdef PHP_WIN32
	phar_unixify_path_separators(mydata->fname, fname_len);
#endif
	p = strrchr(mydata->fname, '/');

	if (p) {
		mydata->ext = memchr(p, '.', (mydata->fname + fname_len) - p);
		if (mydata->ext == p) {
			mydata->ext = memchr(p + 1, '.', (mydata->fname + fname_len) - p - 1);
		}
		if (mydata->ext) {
			mydata->ext_len = (mydata->fname + fname_len) - mydata->ext;
		}
	}

	if (pphar) {
		*pphar = mydata;
	}

	zend_hash_init(&mydata->manifest, sizeof(phar_entry_info),
		zend_get_hash_value, destroy_phar_manifest_entry, 0);
	zend_hash_init(&mydata->mounted_dirs, sizeof(char *),
		zend_get_hash_value, NULL, 0);
	zend_hash_init(&mydata->virtual_dirs, sizeof(char *),
		zend_get_hash_value, NULL, (zend_bool)mydata->is_persistent);
	mydata->fname_len = fname_len;
	snprintf(mydata->version, sizeof(mydata->version), "%s", PHP_PHAR_API_VERSION);
	mydata->is_temporary_alias = alias ? 0 : 1;
	mydata->internal_file_start = -1;
	mydata->fp = NULL;
	mydata->is_writeable = 1;
	mydata->is_brandnew = 1;
	phar_request_initialize();
	zend_hash_str_add_ptr(&(PHAR_G(phar_fname_map)), mydata->fname, fname_len, mydata);

	if (is_data) {
		alias = NULL;
		alias_len = 0;
		mydata->is_data = 1;
		/* assume tar format, PharData can specify other */
		mydata->is_tar = 1;
	} else {
		phar_archive_data *fd_ptr;

		if (alias && NULL != (fd_ptr = zend_hash_str_find_ptr(&(PHAR_G(phar_alias_map)), alias, alias_len))) {
			if (SUCCESS != phar_free_alias(fd_ptr, alias, alias_len)) {
				if (error) {
					spprintf(error, 4096, "phar error: phar \"%s\" cannot set alias \"%s\", already in use by another phar archive", mydata->fname, alias);
				}

				zend_hash_str_del(&(PHAR_G(phar_fname_map)), mydata->fname, fname_len);

				if (pphar) {
					*pphar = NULL;
				}

				return FAILURE;
			}
		}

		mydata->alias = alias ? estrndup(alias, alias_len) : estrndup(mydata->fname, fname_len);
		mydata->alias_len = alias ? alias_len : fname_len;
	}

	if (alias_len && alias) {
		if (NULL == zend_hash_str_add_ptr(&(PHAR_G(phar_alias_map)), alias, alias_len, mydata)) {
			if (options & REPORT_ERRORS) {
				if (error) {
					spprintf(error, 0, "archive \"%s\" cannot be associated with alias \"%s\", already in use", fname, alias);
				}
			}

			zend_hash_str_del(&(PHAR_G(phar_fname_map)), mydata->fname, fname_len);

			if (pphar) {
				*pphar = NULL;
			}

			return FAILURE;
		}
	}

	return SUCCESS;
}
/* }}}*/
