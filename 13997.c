PHP_NAMED_FUNCTION(php_if_ftruncate)
{
	zval *fp;
	long size;
	php_stream *stream;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &fp, &size) == FAILURE) {
		RETURN_FALSE;
	}

	PHP_STREAM_TO_ZVAL(stream, &fp);

	if (!php_stream_truncate_supported(stream)) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Can't truncate this stream!");
		RETURN_FALSE;
	}

	RETURN_BOOL(0 == php_stream_truncate_set_size(stream, size));
}
