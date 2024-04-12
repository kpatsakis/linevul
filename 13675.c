static void php_imagechar(INTERNAL_FUNCTION_PARAMETERS, int mode)
{
	zval *IM;
	long SIZE, X, Y, COL;
	char *C;
	int C_len;
	gdImagePtr im;
	int ch = 0, col, x, y, size, i, l = 0;
	unsigned char *str = NULL;
	gdFontPtr font;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rlllsl", &IM, &SIZE, &X, &Y, &C, &C_len, &COL) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(im, gdImagePtr, &IM, -1, "Image", le_gd);

	col = COL;

	if (mode < 2) {
		ch = (int)((unsigned char)*C);
	} else {
		str = (unsigned char *) estrndup(C, C_len);
		l = strlen((char *)str);
	}

	y = Y;
	x = X;
	size = SIZE;

	font = php_find_gd_font(size TSRMLS_CC);

	switch (mode) {
		case 0:
			gdImageChar(im, font, x, y, ch, col);
			break;
		case 1:
			php_gdimagecharup(im, font, x, y, ch, col);
			break;
		case 2:
			for (i = 0; (i < l); i++) {
				gdImageChar(im, font, x, y, (int) ((unsigned char) str[i]), col);
				x += font->w;
			}
			break;
		case 3: {
			for (i = 0; (i < l); i++) {
				/* php_gdimagecharup(im, font, x, y, (int) str[i], col); */
				gdImageCharUp(im, font, x, y, (int) str[i], col);
				y -= font->w;
			}
			break;
		}
	}
	if (str) {
		efree(str);
	}
	RETURN_TRUE;
}
