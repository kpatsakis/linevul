static ZIPARCHIVE_METHOD(statIndex)
{
	struct zip *intern;
	zval *self = getThis();
	zend_long index, flags = 0;

	struct zip_stat sb;

	if (!self) {
		RETURN_FALSE;
	}

	ZIP_FROM_OBJECT(intern, self);

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "l|l",
			&index, &flags) == FAILURE) {
		return;
	}

	if (zip_stat_index(intern, index, flags, &sb) != 0) {
		RETURN_FALSE;
	}
	RETURN_SB(&sb);
}
