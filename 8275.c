PHP_FUNCTION(imagedestroy)
{
	zval *IM;
	gdImagePtr im;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &IM) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(im, gdImagePtr, &IM, -1, "Image", le_gd);

	zend_list_delete(Z_LVAL_P(IM));

	RETURN_TRUE;
}
