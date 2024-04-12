PHP_FUNCTION(stream_get_line)
{
	char *str = NULL;
	int str_len = 0;
	long max_length;
	zval *zstream;
	char *buf;
	size_t buf_size;
	php_stream *stream;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl|s", &zstream, &max_length, &str, &str_len) == FAILURE) {
		RETURN_FALSE;
	}

	if (max_length < 0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "The maximum allowed length must be greater than or equal to zero");
		RETURN_FALSE;
	}
	if (!max_length) {
		max_length = PHP_SOCK_CHUNK_SIZE;
	}

	php_stream_from_zval(stream, &zstream);

	if ((buf = php_stream_get_record(stream, max_length, &buf_size, str, str_len TSRMLS_CC))) {
		RETURN_STRINGL(buf, buf_size, 0);
	} else {
		RETURN_FALSE;
	}
}
