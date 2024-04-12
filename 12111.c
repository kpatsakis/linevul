PHPAPI PHP_FUNCTION(fseek)
{
	zval *arg1;
	long arg2, whence = SEEK_SET;
	php_stream *stream;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl|l", &arg1, &arg2, &whence) == FAILURE) {
		RETURN_FALSE;
	}

	PHP_STREAM_TO_ZVAL(stream, &arg1);

	RETURN_LONG(php_stream_seek(stream, arg2, whence));
}
