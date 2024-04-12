static PHP_FUNCTION(xmlwriter_start_dtd)
{
	zval *pind;
	xmlwriter_object *intern;
	xmlTextWriterPtr ptr;
	char *name, *pubid = NULL, *sysid = NULL;
	int name_len, pubid_len, sysid_len, retval;

#ifdef ZEND_ENGINE_2
	zval *this = getThis();

	if (this) {
		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s!s!", &name, &name_len, &pubid, &pubid_len, &sysid, &sysid_len) == FAILURE) {
			return;
		}

		XMLWRITER_FROM_OBJECT(intern, this);
	} else
#endif
	{
		if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rs|s!s!", &pind, &name, &name_len, &pubid, &pubid_len, &sysid, &sysid_len) == FAILURE) {
			return;
		}
	
		ZEND_FETCH_RESOURCE(intern,xmlwriter_object *, &pind, -1, "XMLWriter", le_xmlwriter);
	}
	ptr = intern->ptr;

	if (ptr) {
		retval = xmlTextWriterStartDTD(ptr, (xmlChar *)name, (xmlChar *)pubid, (xmlChar *)sysid);
		if (retval != -1) {
			RETURN_TRUE;
		}
	}
	
	RETURN_FALSE;
}
