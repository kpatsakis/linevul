static PHP_NAMED_FUNCTION(zif_zip_close)
{
	zval * zip;
	zip_rsrc *z_rsrc = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "r", &zip) == FAILURE) {
		return;
	}

	if ((z_rsrc = (zip_rsrc *)zend_fetch_resource(Z_RES_P(zip), le_zip_dir_name, le_zip_dir)) == NULL) {
		RETURN_FALSE;
	}

	/* really close the zip will break BC :-D */
	zend_list_close(Z_RES_P(zip));
}
