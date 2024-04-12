PHP_FUNCTION(imagesetbrush)
{
	zval *IM, *TILE;
	gdImagePtr im, tile;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rr", &IM, &TILE) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(im, gdImagePtr, &IM, -1, "Image", le_gd);
	ZEND_FETCH_RESOURCE(tile, gdImagePtr, &TILE, -1, "Image", le_gd);

	gdImageSetBrush(im, tile);

	RETURN_TRUE;
}
