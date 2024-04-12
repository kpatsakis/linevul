ZEND_API int add_index_resource(zval *arg, ulong index, int r) /* {{{ */
{
	zval *tmp;

	MAKE_STD_ZVAL(tmp);
	ZVAL_RESOURCE(tmp, r);

	return zend_hash_index_update(Z_ARRVAL_P(arg), index, (void *) &tmp, sizeof(zval *), NULL);
}
/* }}} */
