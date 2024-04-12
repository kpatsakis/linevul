double AutoFillUploadXmlParser::GetDoubleValue(buzz::XmlParseContext* context,
                                               const char* attribute) {
  char* attr_end = NULL;
  double value = strtod(attribute, &attr_end);
  if (attr_end != NULL && attr_end == attribute) {
    context->RaiseError(XML_ERROR_SYNTAX);
    return 0.0;
  }
  return value;
}
