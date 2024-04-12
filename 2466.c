static ZIPARCHIVE_METHOD(unchangeArchive)
{
	struct zip *intern;
	zval *self = getThis();

	if (!self) {
		RETURN_FALSE;
	}

	ZIP_FROM_OBJECT(intern, self);

	if (zip_unchange_archive(intern) != 0) {
		RETURN_FALSE;
	} else {
		RETURN_TRUE;
	}
}
