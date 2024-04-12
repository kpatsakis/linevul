ZEND_API int add_next_index_null(zval *arg) /* {{{ */
{
	zval *tmp;

	MAKE_STD_ZVAL(tmp);
	ZVAL_NULL(tmp);

	return zend_hash_next_index_insert(Z_ARRVAL_P(arg), &tmp, sizeof(zval *), NULL);
}
/* }}} */
