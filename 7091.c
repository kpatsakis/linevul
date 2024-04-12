php_http_url_t *php_http_url_from_zval(zval *value, unsigned flags TSRMLS_DC)
{
	zval *zcpy;
	php_http_url_t *purl;

	switch (Z_TYPE_P(value)) {
	case IS_ARRAY:
	case IS_OBJECT:
		purl = php_http_url_from_struct(HASH_OF(value));
		break;

	default:
		zcpy = php_http_ztyp(IS_STRING, value);
		purl = php_http_url_parse(Z_STRVAL_P(zcpy), Z_STRLEN_P(zcpy), flags TSRMLS_CC);
		zval_ptr_dtor(&zcpy);
	}

	return purl;
}
