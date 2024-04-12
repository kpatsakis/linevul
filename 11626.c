PHP_NAMED_FUNCTION(php_if_tmpfile)
{
	php_stream *stream;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	stream = php_stream_fopen_tmpfile();

	if (stream) {
		php_stream_to_zval(stream, return_value);
	} else {
		RETURN_FALSE;
	}
}
