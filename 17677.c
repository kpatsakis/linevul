static void spl_filesystem_file_free_line(spl_filesystem_object *intern TSRMLS_DC) /* {{{ */
{
	if (intern->u.file.current_line) {
		efree(intern->u.file.current_line);
		intern->u.file.current_line = NULL;
	}
	if (intern->u.file.current_zval) {
		zval_ptr_dtor(&intern->u.file.current_zval);
		intern->u.file.current_zval = NULL;
	}
} /* }}} */
