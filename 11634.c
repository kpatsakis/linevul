raptor_rdfxml_comment_handler(void *user_data, raptor_xml_element* xml_element,
                              const unsigned char *s)
{
  raptor_parser* rdf_parser = (raptor_parser*)user_data;
  raptor_rdfxml_parser* rdf_xml_parser;
  raptor_rdfxml_element* element;

  if(rdf_parser->failed || !xml_element)
    return;

  rdf_xml_parser = (raptor_rdfxml_parser*)rdf_parser->context;
  element = rdf_xml_parser->current_element;

  if(element) {
    if(element->child_content_type == RAPTOR_RDFXML_ELEMENT_CONTENT_TYPE_XML_LITERAL)
      raptor_xml_writer_comment(rdf_xml_parser->xml_writer, s);
  }
  

#ifdef RAPTOR_DEBUG_VERBOSE
  RAPTOR_DEBUG2("XML Comment '%s'\n", s);
#endif
}
