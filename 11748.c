ZEND_API int zend_declare_property_double(zend_class_entry *ce, const char *name, int name_length, double value, int access_type TSRMLS_DC) /* {{{ */
{
	zval *property;

	if (ce->type & ZEND_INTERNAL_CLASS) {
		ALLOC_PERMANENT_ZVAL(property);
	} else {
		ALLOC_ZVAL(property);
	}
	INIT_PZVAL(property);
	ZVAL_DOUBLE(property, value);
	return zend_declare_property(ce, name, name_length, property, access_type TSRMLS_CC);
}
/* }}} */
