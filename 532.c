PHP_FUNCTION(curl_errno)
{
	zval		*zid;
	php_curl	*ch;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "r", &zid) == FAILURE) {
		return;
	}

	if ((ch = (php_curl*)zend_fetch_resource(Z_RES_P(zid), le_curl_name, le_curl)) == NULL) {
		RETURN_FALSE;
	}

	RETURN_LONG(ch->err.no);
}
