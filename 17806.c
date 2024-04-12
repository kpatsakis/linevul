void _xml_processingInstructionHandler(void *userData, const XML_Char *target, const XML_Char *data)
{
	xml_parser *parser = (xml_parser *)userData;

	if (parser && parser->processingInstructionHandler) {
		zval *retval, *args[3];

		args[0] = _xml_resource_zval(parser->index);
		args[1] = _xml_xmlchar_zval(target, 0, parser->target_encoding);
		args[2] = _xml_xmlchar_zval(data, 0, parser->target_encoding);
		if ((retval = xml_call_handler(parser, parser->processingInstructionHandler, parser->processingInstructionPtr, 3, args))) {
			zval_ptr_dtor(&retval);
		}
	}
}
