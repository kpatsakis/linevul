PHP_FUNCTION(dom_document_get_elements_by_tag_name)
{
	zval *id;
	xmlDocPtr docp;
	int name_len;
	dom_object *intern, *namednode;
	char *name;
	xmlChar *local;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os", &id, dom_document_class_entry, &name, &name_len) == FAILURE) {
		return;
	}

	DOM_GET_OBJ(docp, id, xmlDocPtr, intern);

	php_dom_create_interator(return_value, DOM_NODELIST TSRMLS_CC);
	namednode = (dom_object *)zend_objects_get_address(return_value TSRMLS_CC);
	local = xmlCharStrndup(name, name_len);
	dom_namednode_iter(intern, 0, namednode, NULL, local, NULL TSRMLS_CC);
}
