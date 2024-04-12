raptor_rdfxml_end_element_grammar(raptor_parser *rdf_parser,
                                  raptor_rdfxml_element *element) 
{
  raptor_rdfxml_parser *rdf_xml_parser;
  raptor_state state;
  int finished;
  raptor_xml_element* xml_element = element->xml_element;
  raptor_qname* el_qname;
  const unsigned char *el_name;
  int element_in_rdf_ns;
  raptor_uri* element_name_uri;

  rdf_xml_parser = (raptor_rdfxml_parser*)rdf_parser->context;

  el_qname = raptor_xml_element_get_name(xml_element);
  el_name = el_qname->local_name;
  element_in_rdf_ns= (el_qname->nspace && el_qname->nspace->is_rdf_ms);
  element_name_uri = el_qname->uri;


  state = element->state;
#ifdef RAPTOR_DEBUG_VERBOSE
  RAPTOR_DEBUG2("Starting in state %s\n", raptor_rdfxml_state_as_string(state));
#endif

  finished= 0;
  while(!finished) {
    switch(state) {
      case RAPTOR_STATE_SKIPPING:
        finished = 1;
        break;

      case RAPTOR_STATE_UNKNOWN:
        finished = 1;
        break;

      case RAPTOR_STATE_NODE_ELEMENT_LIST:
        if(element_in_rdf_ns && 
           raptor_uri_equals(element_name_uri,
                             RAPTOR_RDF_RDF_URI(rdf_parser->world))) {
          /* end of RDF - boo hoo */
          state = RAPTOR_STATE_UNKNOWN;
          finished = 1;
          break;
        }
        /* When scanning, another element ending is outside the RDF
         * world so this can happen without further work
         */
        if(RAPTOR_OPTIONS_GET_NUMERIC(rdf_parser, RAPTOR_OPTION_SCANNING)) {
          state = RAPTOR_STATE_UNKNOWN;
          finished = 1;
          break;
        }
        /* otherwise found some junk after RDF content in an RDF-only 
         * document (probably never get here since this would be
         * a mismatched XML tag and cause an error earlier)
         */
        raptor_rdfxml_update_document_locator(rdf_parser);
        raptor_parser_warning(rdf_parser,
                              "Element '%s' ended, expected end of RDF element",
                              el_name);
        state = RAPTOR_STATE_UNKNOWN;
        finished = 1;
        break;


      case RAPTOR_STATE_DESCRIPTION:
      case RAPTOR_STATE_NODE_ELEMENT:
      case RAPTOR_STATE_PARSETYPE_RESOURCE:

        /* If there is a parent element containing this element and
         * the parent isn't a description, has an identifier,
         * create the statement between this node using parent property
         * (Need to check for identifier so that top-level typed nodes
         * don't get connect to <rdf:RDF> parent element)
         */
        if(state == RAPTOR_STATE_NODE_ELEMENT && 
           element->parent && element->parent->subject) {
          raptor_rdfxml_generate_statement(rdf_parser, 
                                           element->parent->subject,
                                           element_name_uri,
                                           element->subject,
                                           NULL,
                                           element);
        } else if(state == RAPTOR_STATE_PARSETYPE_RESOURCE && 
                  element->parent && element->parent->subject) {
          /* Handle rdf:li as the rdf:parseType="resource" property */
          if(element_in_rdf_ns && 
             raptor_uri_equals(element_name_uri,
                               RAPTOR_RDF_li_URI(rdf_parser->world))) {
            raptor_uri* ordinal_predicate_uri;
            
            element->parent->last_ordinal++;
            ordinal_predicate_uri = raptor_new_uri_from_rdf_ordinal(rdf_parser->world, element->parent->last_ordinal);

            raptor_rdfxml_generate_statement(rdf_parser, 
                                             element->parent->subject,
                                             ordinal_predicate_uri,
                                             element->subject,
                                             element->reified,
                                             element->parent);
            raptor_free_uri(ordinal_predicate_uri);
          } else {
            raptor_rdfxml_generate_statement(rdf_parser, 
                                             element->parent->subject,
                                             element_name_uri,
                                             element->subject,
                                             element->reified,
                                             element->parent);
          }
        }
        finished = 1;
        break;

      case RAPTOR_STATE_PARSETYPE_COLLECTION:

        finished = 1;
        break;

      case RAPTOR_STATE_PARSETYPE_OTHER:
        /* FALLTHROUGH */

      case RAPTOR_STATE_PARSETYPE_LITERAL:
        element->parent->content_type = RAPTOR_RDFXML_ELEMENT_CONTENT_TYPE_XML_LITERAL;

        raptor_xml_writer_end_element(rdf_xml_parser->xml_writer, xml_element);

        finished = 1;
        break;


      case RAPTOR_STATE_PROPERTYELT:
      case RAPTOR_STATE_MEMBER_PROPERTYELT:
        /* A property element
         *   http://www.w3.org/TR/rdf-syntax-grammar/#propertyElt
         *
         * Literal content part is handled here.
         * The element content is handled in the internal states
         * Empty content is checked here.
         */

        if(element->content_type == RAPTOR_RDFXML_ELEMENT_CONTENT_TYPE_PROPERTY_CONTENT) {
          if(xml_element->content_cdata_seen) 
            element->content_type = RAPTOR_RDFXML_ELEMENT_CONTENT_TYPE_LITERAL;
          else if(xml_element->content_element_seen) 
            element->content_type = RAPTOR_RDFXML_ELEMENT_CONTENT_TYPE_PROPERTIES;
          else {
            /* Empty Literal */
            element->content_type = RAPTOR_RDFXML_ELEMENT_CONTENT_TYPE_LITERAL;
          }
          
        }


        /* Handle terminating a rdf:parseType="Collection" list */
        if(element->child_content_type == RAPTOR_RDFXML_ELEMENT_CONTENT_TYPE_COLLECTION ||
           element->child_content_type == RAPTOR_RDFXML_ELEMENT_CONTENT_TYPE_DAML_COLLECTION) {
          raptor_term* nil_term;

          if(element->child_content_type == RAPTOR_RDFXML_ELEMENT_CONTENT_TYPE_DAML_COLLECTION) {
            raptor_uri* nil_uri = RAPTOR_DAML_nil_URI(rdf_xml_parser);
            nil_term = raptor_new_term_from_uri(rdf_parser->world, nil_uri);
          } else {
            nil_term = raptor_term_copy(RAPTOR_RDF_nil_term(rdf_parser->world));
          }
          
          if(!element->tail_id) {
            /* If No List: set object of statement to rdf:nil */
            element->object = raptor_term_copy(nil_term);
          } else {
            raptor_uri* rest_uri = NULL;
            raptor_term* tail_id_term;
            
            if(element->child_content_type == RAPTOR_RDFXML_ELEMENT_CONTENT_TYPE_DAML_COLLECTION)
              rest_uri =  RAPTOR_DAML_rest_URI(rdf_xml_parser);
            else
              rest_uri = RAPTOR_RDF_rest_URI(rdf_parser->world);

            tail_id_term = raptor_new_term_from_blank(rdf_parser->world, 
                                                      element->tail_id);

            /* terminate the list */
            raptor_rdfxml_generate_statement(rdf_parser, 
                                             tail_id_term,
                                             rest_uri,
                                             nil_term,
                                             NULL,
                                             NULL);

            raptor_free_term(tail_id_term);
          }

          raptor_free_term(nil_term);
          
        } /* end rdf:parseType="Collection" termination */
        

#ifdef RAPTOR_DEBUG_VERBOSE
        RAPTOR_DEBUG3("Content type %s (%d)\n",
                      raptor_rdfxml_element_content_type_as_string(element->content_type),
                      element->content_type);
#endif

        switch(element->content_type) {
          case RAPTOR_RDFXML_ELEMENT_CONTENT_TYPE_RESOURCE:

            if(raptor_rdfxml_element_has_property_attributes(element) &&
               element->child_state == RAPTOR_STATE_DESCRIPTION) {
              raptor_parser_error(rdf_parser,
                                  "Property element '%s' has both property attributes and a node element content",
                                  el_name);
              state = RAPTOR_STATE_SKIPPING;
              element->child_state = RAPTOR_STATE_SKIPPING;
              break;
            }

            if(!element->object) {
              if(element->rdf_attr[RDF_NS_resource]) {
                raptor_uri* resource_uri;
                resource_uri = raptor_new_uri_relative_to_base(rdf_parser->world,
                                                               raptor_rdfxml_inscope_base_uri(rdf_parser),
                                                               (const unsigned char*)element->rdf_attr[RDF_NS_resource]);
                if(!resource_uri)
                  goto oom;
                
                element->object = raptor_new_term_from_uri(rdf_parser->world,
                                                           resource_uri);
                raptor_free_uri(resource_uri);

                RAPTOR_FREE(char*, element->rdf_attr[RDF_NS_resource]);
                element->rdf_attr[RDF_NS_resource] = NULL;
                if(!element->object)
                  goto oom;
                element->content_type = RAPTOR_RDFXML_ELEMENT_CONTENT_TYPE_RESOURCE;
              } else if(element->rdf_attr[RDF_NS_nodeID]) {
                unsigned char* resource_id;
                resource_id = raptor_world_internal_generate_id(rdf_parser->world,
                                                                (unsigned char*)element->rdf_attr[RDF_NS_nodeID]);
                if(!resource_id)
                  goto oom;
                
                element->object = raptor_new_term_from_blank(rdf_parser->world,
                                                             resource_id);
                RAPTOR_FREE(char*, resource_id);
                element->rdf_attr[RDF_NS_nodeID] = NULL;
                if(!element->object)
                  goto oom;

                element->content_type = RAPTOR_RDFXML_ELEMENT_CONTENT_TYPE_RESOURCE;
                if(!raptor_valid_xml_ID(rdf_parser,
                                        element->object->value.blank.string)) {
                  raptor_parser_error(rdf_parser, "Illegal rdf:nodeID value '%s'", (const char*)element->object->value.blank.string);
                  state = RAPTOR_STATE_SKIPPING;
                  element->child_state = RAPTOR_STATE_SKIPPING;
                  break;
                }
              } else {
                unsigned char* resource_id;
                resource_id = raptor_world_generate_bnodeid(rdf_parser->world);
                if(!resource_id)
                  goto oom;
                
                element->object = raptor_new_term_from_blank(rdf_parser->world,
                                                             resource_id);
                RAPTOR_FREE(char*, resource_id);

                if(!element->object)
                  goto oom;
                element->content_type = RAPTOR_RDFXML_ELEMENT_CONTENT_TYPE_RESOURCE;
              }

              if(raptor_rdfxml_process_property_attributes(rdf_parser, element, 
                                                           element->parent, 
                                                           element->object))
                 goto oom;

            }

            /* We know object is a resource, so delete any unsignficant
             * whitespace so that FALLTHROUGH code below finds the object.
             */
            if(xml_element->content_cdata_length) {
              raptor_free_stringbuffer(xml_element->content_cdata_sb);
              xml_element->content_cdata_sb = NULL;
              xml_element->content_cdata_length = 0;
            }

            /* FALLTHROUGH */
          case RAPTOR_RDFXML_ELEMENT_CONTENT_TYPE_LITERAL:

            if(element->content_type == RAPTOR_RDFXML_ELEMENT_CONTENT_TYPE_LITERAL) {

              if(RAPTOR_OPTIONS_GET_NUMERIC(rdf_parser, RAPTOR_OPTION_ALLOW_BAGID)) {
                /* Only an empty literal can have a rdf:bagID */
                if(element->bag) {
                  if(xml_element->content_cdata_length > 0) {
                    raptor_parser_error(rdf_parser,
                                        "rdf:bagID is forbidden on a literal property element '%s'.",
                                        el_name);

                    /* prevent this being used later either */
                    element->rdf_attr[RDF_NS_bagID] = NULL;
                  } else {
                    raptor_rdfxml_generate_statement(rdf_parser, 
                                                     element->bag,
                                                     RAPTOR_RDF_type_URI(rdf_parser->world),
                                                     RAPTOR_RDF_Bag_term(rdf_parser->world),
                                                     NULL,
                                                     NULL);
                  }
                }
              } /* if rdf:bagID */

              /* If there is empty literal content with properties
               * generate a node to hang properties off 
               */
              if(raptor_rdfxml_element_has_property_attributes(element) &&
                 xml_element->content_cdata_length > 0) {
                raptor_parser_error(rdf_parser,
                                    "Literal property element '%s' has property attributes", 
                                    el_name);
                state = RAPTOR_STATE_SKIPPING;
                element->child_state = RAPTOR_STATE_SKIPPING;
                break;
              }

              if(element->content_type == RAPTOR_RDFXML_ELEMENT_CONTENT_TYPE_LITERAL &&
                 raptor_rdfxml_element_has_property_attributes(element) &&
                 !element->object) {
                unsigned char* object_id;
                object_id = raptor_world_generate_bnodeid(rdf_parser->world);
                if(!object_id)
                  goto oom;
                
                element->object = raptor_new_term_from_blank(rdf_parser->world,
                                                             object_id);
                RAPTOR_FREE(char*, object_id);

                if(!element->object)
                  goto oom;
                element->content_type = RAPTOR_RDFXML_ELEMENT_CONTENT_TYPE_RESOURCE;
              }
              
              if(raptor_rdfxml_process_property_attributes(rdf_parser, element, 
                                                           element,
                                                           element->object))
                 goto oom;
            }
            

            /* just be friendly to older compilers and don't declare
             * variables in the middle of a block
             */
            if(1) {
              raptor_uri *predicate_uri = NULL;
              int predicate_ordinal = -1;
              raptor_term* object_term = NULL;
              
              if(state == RAPTOR_STATE_MEMBER_PROPERTYELT) {
                predicate_ordinal = ++element->parent->last_ordinal;
                predicate_uri = raptor_new_uri_from_rdf_ordinal(rdf_parser->world,
                                                                predicate_ordinal);

              } else {
                predicate_uri = element_name_uri;
              }


              if(element->content_type == RAPTOR_RDFXML_ELEMENT_CONTENT_TYPE_LITERAL) {
                unsigned char* literal = NULL;
                raptor_uri* literal_datatype;
                unsigned char* literal_language = NULL;

                /* an empty stringbuffer - empty CDATA - is OK */
                if(raptor_stringbuffer_length(xml_element->content_cdata_sb)) {
                  literal = raptor_stringbuffer_as_string(xml_element->content_cdata_sb);
                  if(!literal)
                    goto oom;
                }
                
                literal_datatype = element->object_literal_datatype;
                if(!literal_datatype)
                  literal_language = (unsigned char*)raptor_sax2_inscope_xml_language(rdf_xml_parser->sax2);

                if(!literal_datatype && literal &&
                   !raptor_unicode_check_utf8_nfc_string(literal,
                                                         xml_element->content_cdata_length,
                                                         NULL)) {
                  const char *message;
                  message = "Property element '%s' has a string not in Unicode Normal Form C: %s";
                  raptor_rdfxml_update_document_locator(rdf_parser);
                  if(RAPTOR_OPTIONS_GET_NUMERIC(rdf_parser, RAPTOR_OPTION_NON_NFC_FATAL))
                    raptor_parser_error(rdf_parser, message, el_name, literal);
                  else
                    raptor_parser_warning(rdf_parser, message, el_name, literal);
                }

                object_term = raptor_new_term_from_literal(rdf_parser->world,
                                                           literal,
                                                           literal_datatype,
                                                           literal_language);
              } else {
                object_term = raptor_term_copy(element->object);
              }

              raptor_rdfxml_generate_statement(rdf_parser, 
                                               element->parent->subject,
                                               predicate_uri,
                                               object_term,
                                               element->reified,
                                               element->parent);

              if(predicate_ordinal >= 0)
                raptor_free_uri(predicate_uri);

              raptor_free_term(object_term);
            }
            
            break;

        case RAPTOR_RDFXML_ELEMENT_CONTENT_TYPE_PRESERVED:
        case RAPTOR_RDFXML_ELEMENT_CONTENT_TYPE_XML_LITERAL:
            {
              unsigned char *buffer;
              size_t length;
              raptor_term* xmlliteral_term = NULL;
              
              if(rdf_xml_parser->xml_writer) {
                raptor_xml_writer_flush(rdf_xml_parser->xml_writer);

                raptor_free_iostream(rdf_xml_parser->iostream);
                rdf_xml_parser->iostream = NULL;
                
                buffer = (unsigned char*)rdf_xml_parser->xml_content;
                length = rdf_xml_parser->xml_content_length;
              } else {
                buffer = raptor_stringbuffer_as_string(xml_element->content_cdata_sb);
                length = xml_element->content_cdata_length;
              }

              if(!raptor_unicode_check_utf8_nfc_string(buffer, length, NULL)) {
                const char *message;
                message = "Property element '%s' has XML literal content not in Unicode Normal Form C: %s";
                raptor_rdfxml_update_document_locator(rdf_parser);
                if(RAPTOR_OPTIONS_GET_NUMERIC(rdf_parser, RAPTOR_OPTION_NON_NFC_FATAL))
                  raptor_parser_error(rdf_parser, message, el_name, buffer);
                else
                  raptor_parser_warning(rdf_parser, message, el_name, buffer);
              }

              xmlliteral_term = raptor_new_term_from_literal(rdf_parser->world,
                                                             buffer,
                                                             RAPTOR_RDF_XMLLiteral_URI(rdf_parser->world),
                                                             NULL);
              
              if(state == RAPTOR_STATE_MEMBER_PROPERTYELT) {
                raptor_uri* predicate_uri;
                
                element->parent->last_ordinal++;
                predicate_uri = raptor_new_uri_from_rdf_ordinal(rdf_parser->world, element->parent->last_ordinal);

                raptor_rdfxml_generate_statement(rdf_parser, 
                                                 element->parent->subject,
                                                 predicate_uri,
                                                 xmlliteral_term,
                                                 element->reified,
                                                 element->parent);

                raptor_free_uri(predicate_uri);
              } else {
                raptor_rdfxml_generate_statement(rdf_parser, 
                                                 element->parent->subject,
                                                 element_name_uri,
                                                 xmlliteral_term,
                                                 element->reified,
                                                 element->parent);
              }
              
              raptor_free_term(xmlliteral_term);

              /* Finish the xml writer iostream for parseType="Literal" */
              if(rdf_xml_parser->xml_writer) {
                raptor_free_xml_writer(rdf_xml_parser->xml_writer);
                RAPTOR_FREE(char*, rdf_xml_parser->xml_content);
                rdf_xml_parser->xml_content = NULL;
                rdf_xml_parser->xml_content_length = 0;
              }
            }
            
          break;

          case RAPTOR_RDFXML_ELEMENT_CONTENT_TYPE_COLLECTION:
          case RAPTOR_RDFXML_ELEMENT_CONTENT_TYPE_DAML_COLLECTION:

          case RAPTOR_RDFXML_ELEMENT_CONTENT_TYPE_NODES:
          case RAPTOR_RDFXML_ELEMENT_CONTENT_TYPE_PROPERTIES:
          case RAPTOR_RDFXML_ELEMENT_CONTENT_TYPE_PROPERTY_CONTENT:
            
          case RAPTOR_RDFXML_ELEMENT_CONTENT_TYPE_UNKNOWN:
          case RAPTOR_RDFXML_ELEMENT_CONTENT_TYPE_LAST:
          default:
            raptor_parser_fatal_error(rdf_parser,
                                      "%s: Internal error in state RAPTOR_STATE_PROPERTYELT - got unexpected content type %s (%d)",
                                      __func__,
                                      raptor_rdfxml_element_content_type_as_string(element->content_type),
                                      element->content_type);
        } /* end switch */

      finished = 1;
      break;

      case RAPTOR_STATE_INVALID:
      default:
        raptor_parser_fatal_error(rdf_parser,
                                  "%s: Internal error - unexpected parser state %d - %s",
                                  __func__,
                                  state,
                                  raptor_rdfxml_state_as_string(state));
        finished = 1;

    } /* end switch */

    if(state != element->state) {
      element->state = state;
#ifdef RAPTOR_DEBUG_VERBOSE
      RAPTOR_DEBUG3("Moved to state %d - %s\n", state,
                    raptor_rdfxml_state_as_string(state));
#endif
    }

  } /* end while */

#ifdef RAPTOR_DEBUG_VERBOSE
  RAPTOR_DEBUG2("Ending in state %s\n", raptor_rdfxml_state_as_string(state));
#endif

  return;

  oom:
  raptor_parser_fatal_error(rdf_parser, "Out of memory, skipping");
  element->state = RAPTOR_STATE_SKIPPING;
}
