ZEND_API int zend_declare_class_constant_stringl(zend_class_entry *ce, const char *name, size_t name_length, const char *value, size_t value_length TSRMLS_DC) /* {{{ */
{
	zval *constant;

	if (ce->type & ZEND_INTERNAL_CLASS) {
		ALLOC_PERMANENT_ZVAL(constant);
		ZVAL_STRINGL(constant, zend_strndup(value, value_length), value_length, 0);
	} else {
		ALLOC_ZVAL(constant);
		ZVAL_STRINGL(constant, value, value_length, 1);
	}
	INIT_PZVAL(constant);
	return zend_declare_class_constant(ce, name, name_length, constant TSRMLS_CC);
}
/* }}} */
