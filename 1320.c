static ZIPARCHIVE_METHOD(getStream)
{
	struct zip *intern;
	zval *self = getThis();
	struct zip_stat sb;
	char *mode = "rb";
	zend_string *filename;
	php_stream *stream;
	ze_zip_object *obj;

	if (!self) {
		RETURN_FALSE;
	}

	ZIP_FROM_OBJECT(intern, self);

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "P", &filename) == FAILURE) {
		return;
	}

	if (zip_stat(intern, ZSTR_VAL(filename), 0, &sb) != 0) {
		RETURN_FALSE;
	}

	obj = Z_ZIP_P(self);

	stream = php_stream_zip_open(obj->filename, ZSTR_VAL(filename), mode STREAMS_CC);
	if (stream) {
		php_stream_to_zval(stream, return_value);
	} else {
		RETURN_FALSE;
	}
}
