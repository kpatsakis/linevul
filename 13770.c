PHP_FUNCTION(imageflip)
{
	zval *IM;
	long mode;
	gdImagePtr im;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &IM, &mode) == FAILURE)  {
		return;
	}

	ZEND_FETCH_RESOURCE(im, gdImagePtr, &IM, -1, "Image", le_gd);

	switch (mode) {
		case GD_FLIP_VERTICAL:
			gdImageFlipVertical(im);
			break;

		case GD_FLIP_HORINZONTAL:
			gdImageFlipHorizontal(im);
			break;

		case GD_FLIP_BOTH:
			gdImageFlipBoth(im);
			break;

		default:
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "Unknown flip mode");
			RETURN_FALSE;
	}

	RETURN_TRUE;
}
