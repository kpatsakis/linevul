PHP_FUNCTION(dom_document_create_entity_reference)
{
	zval *id;
	xmlNode *node;
	xmlDocPtr docp = NULL;
	dom_object *intern;
	int ret, name_len;
	char *name;

	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os", &id, dom_document_class_entry, &name, &name_len) == FAILURE) {
		return;
	}

	DOM_GET_OBJ(docp, id, xmlDocPtr, intern);

	if (xmlValidateName((xmlChar *) name, 0) != 0) {
		php_dom_throw_error(INVALID_CHARACTER_ERR, dom_get_strict_error(intern->document) TSRMLS_CC);
		RETURN_FALSE;
	}

	node = xmlNewReference(docp, name);
	if (!node) {
		RETURN_FALSE;
	}

	DOM_RET_OBJ((xmlNodePtr) node, &ret, intern);
}
