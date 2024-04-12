PHPAPI PHP_FUNCTION(fwrite)
{
	zval *arg1;
	char *arg2;
	int arg2len;
	int ret;
	int num_bytes;
	long arg3 = 0;
	char *buffer = NULL;
	php_stream *stream;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rs|l", &arg1, &arg2, &arg2len, &arg3) == FAILURE) {
		RETURN_FALSE;
	}

	if (ZEND_NUM_ARGS() == 2) {
		num_bytes = arg2len;
	} else {
		num_bytes = MAX(0, MIN((int)arg3, arg2len));
	}

	if (!num_bytes) {
		RETURN_LONG(0);
	}

	PHP_STREAM_TO_ZVAL(stream, &arg1);

	ret = php_stream_write(stream, buffer ? buffer : arg2, num_bytes);
	if (buffer) {
		efree(buffer);
	}

	RETURN_LONG(ret);
}
