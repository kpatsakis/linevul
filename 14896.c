PHP_FUNCTION(money_format)
{
	size_t format_len = 0;
	char *format, *p, *e;
	double value;
	zend_bool check = 0;
	zend_string *str;
	ssize_t res_len;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "sd", &format, &format_len, &value) == FAILURE) {
		return;
	}

	p = format;
	e = p + format_len;
	while ((p = memchr(p, '%', (e - p)))) {
		if (*(p + 1) == '%') {
			p += 2;
		} else if (!check) {
			check = 1;
			p++;
		} else {
			php_error_docref(NULL, E_WARNING, "Only a single %%i or %%n token can be used");
			RETURN_FALSE;
		}
	}

	str = zend_string_alloc(format_len + 1024, 0);
	if ((res_len = strfmon(ZSTR_VAL(str), ZSTR_LEN(str), format, value)) < 0) {
		zend_string_free(str);
		RETURN_FALSE;
	}
	ZSTR_LEN(str) = (size_t)res_len;
	ZSTR_VAL(str)[ZSTR_LEN(str)] = '\0';

	RETURN_NEW_STR(zend_string_truncate(str, ZSTR_LEN(str), 0));
}
