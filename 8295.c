ZEND_API zend_class_entry *zend_register_internal_interface(zend_class_entry *orig_class_entry TSRMLS_DC) /* {{{ */
{
	return do_register_internal_class(orig_class_entry, ZEND_ACC_INTERFACE TSRMLS_CC);
}
/* }}} */
