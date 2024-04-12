ZEND_API int add_next_index_double(zval *arg, double d) /* {{{ */
{
	zval *tmp;

	MAKE_STD_ZVAL(tmp);
	ZVAL_DOUBLE(tmp, d);

	return zend_hash_next_index_insert(Z_ARRVAL_P(arg), &tmp, sizeof(zval *), NULL);
}
/* }}} */
