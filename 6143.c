 PHP_FUNCTION(xml_parser_get_option)
 {
	xml_parser *parser;
	zval *pind;
	long opt;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rl", &pind, &opt) == FAILURE) {
		return;
	}
	ZEND_FETCH_RESOURCE(parser,xml_parser *, &pind, -1, "XML Parser", le_xml_parser);

	switch (opt) {
		case PHP_XML_OPTION_CASE_FOLDING:
			RETURN_LONG(parser->case_folding);
			break;
		case PHP_XML_OPTION_TARGET_ENCODING:
			RETURN_STRING(parser->target_encoding, 1);
			break;
		default:
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "Unknown option");
			RETURN_FALSE;
			break;
	}

	RETVAL_FALSE;	/* never reached */
 }
