 PHP_FUNCTION(xml_set_processing_instruction_handler)
 {
	xml_parser *parser;
	zval *pind, **hdl;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rZ", &pind, &hdl) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(parser,xml_parser *, &pind, -1, "XML Parser", le_xml_parser);

	xml_set_handler(&parser->processingInstructionHandler, hdl);
	XML_SetProcessingInstructionHandler(parser->parser, _xml_processingInstructionHandler);
	RETVAL_TRUE;
 }
