PHP_FUNCTION(pathinfo)
{
	zval tmp;
	char *path, *dirname;
	size_t path_len;
	int have_basename;
	zend_long opt = PHP_PATHINFO_ALL;
	zend_string *ret = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s|l", &path, &path_len, &opt) == FAILURE) {
		return;
	}

	have_basename = ((opt & PHP_PATHINFO_BASENAME) == PHP_PATHINFO_BASENAME);

	array_init(&tmp);

	if ((opt & PHP_PATHINFO_DIRNAME) == PHP_PATHINFO_DIRNAME) {
		dirname = estrndup(path, path_len);
		php_dirname(dirname, path_len);
		if (*dirname) {
			add_assoc_string(&tmp, "dirname", dirname);
		}
		efree(dirname);
	}

	if (have_basename) {
		ret = php_basename(path, path_len, NULL, 0);
		add_assoc_str(&tmp, "basename", zend_string_copy(ret));
	}

	if ((opt & PHP_PATHINFO_EXTENSION) == PHP_PATHINFO_EXTENSION) {
		const char *p;
		ptrdiff_t idx;

		if (!have_basename) {
			ret = php_basename(path, path_len, NULL, 0);
		}

		p = zend_memrchr(ZSTR_VAL(ret), '.', ZSTR_LEN(ret));

		if (p) {
			idx = p - ZSTR_VAL(ret);
			add_assoc_stringl(&tmp, "extension", ZSTR_VAL(ret) + idx + 1, ZSTR_LEN(ret) - idx - 1);
		}
	}

	if ((opt & PHP_PATHINFO_FILENAME) == PHP_PATHINFO_FILENAME) {
		const char *p;
		ptrdiff_t idx;

		/* Have we already looked up the basename? */
		if (!have_basename && !ret) {
			ret = php_basename(path, path_len, NULL, 0);
		}

		p = zend_memrchr(ZSTR_VAL(ret), '.', ZSTR_LEN(ret));

		idx = p ? (p - ZSTR_VAL(ret)) : ZSTR_LEN(ret);
		add_assoc_stringl(&tmp, "filename", ZSTR_VAL(ret), idx);
	}

	if (ret) {
		zend_string_release(ret);
	}

	if (opt == PHP_PATHINFO_ALL) {
		ZVAL_COPY_VALUE(return_value, &tmp);
	} else {
		zval *element;
		if ((element = zend_hash_get_current_data(Z_ARRVAL(tmp))) != NULL) {
			ZVAL_DEREF(element);
			ZVAL_COPY(return_value, element);
		} else {
			ZVAL_EMPTY_STRING(return_value);
		}
		zval_ptr_dtor(&tmp);
	}
}
