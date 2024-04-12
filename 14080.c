PHP_FUNCTION(stream_set_write_buffer)
{
	zval *arg1;
	int ret;
	long arg2;
	size_t buff;
	php_stream *stream;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &arg1, &arg2) == FAILURE) {
		RETURN_FALSE;
	}

	php_stream_from_zval(stream, &arg1);

	buff = arg2;

	/* if buff is 0 then set to non-buffered */
	if (buff == 0) {
		ret = php_stream_set_option(stream, PHP_STREAM_OPTION_WRITE_BUFFER, PHP_STREAM_BUFFER_NONE, NULL);
	} else {
		ret = php_stream_set_option(stream, PHP_STREAM_OPTION_WRITE_BUFFER, PHP_STREAM_BUFFER_FULL, &buff);
	}

	RETURN_LONG(ret == 0 ? 0 : EOF);
}
