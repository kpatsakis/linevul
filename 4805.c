raptor_rdfxml_end_element_handler(void *user_data, 
                                  raptor_xml_element* xml_element)
{
  raptor_parser* rdf_parser;
  raptor_rdfxml_parser* rdf_xml_parser;
  raptor_rdfxml_element* element;

  rdf_parser = (raptor_parser*)user_data;
  rdf_xml_parser = (raptor_rdfxml_parser*)rdf_parser->context;

  if(!rdf_parser->failed) {
    raptor_rdfxml_update_document_locator(rdf_parser);

    raptor_rdfxml_end_element_grammar(rdf_parser,
                                      rdf_xml_parser->current_element);
  }
  
  element = raptor_rdfxml_element_pop(rdf_xml_parser);
  if(element) {
    if(element->parent) {
      /* Do not change this; PROPERTYELT will turn into MEMBER if necessary
       * See the switch case for MEMBER / PROPERTYELT where the test is done.
       *
       * PARSETYPE_RESOURCE should never be propogated up since it
       * will turn the next child (node) element into a property
       */
      if(element->state != RAPTOR_STATE_MEMBER_PROPERTYELT &&
         element->state != RAPTOR_STATE_PARSETYPE_RESOURCE)
        element->parent->child_state = element->state;
    }
  
    raptor_free_rdfxml_element(element);
  }
}
