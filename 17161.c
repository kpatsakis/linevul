int dom_document_implementation_read(dom_object *obj, zval **retval TSRMLS_DC)
{
	ALLOC_ZVAL(*retval);
	php_dom_create_implementation(retval TSRMLS_CC);
	return SUCCESS;
}
