static void php_zip_free_prop_handler(zval *el) /* {{{ */ {
	pefree(Z_PTR_P(el), 1);
} /* }}} */
