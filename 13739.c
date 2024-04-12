raptor_rss_end_element_handler(void *user_data, 
                               raptor_xml_element* xml_element)
{
  raptor_parser* rdf_parser;
  raptor_rss_parser* rss_parser;
#ifdef RAPTOR_DEBUG
  const unsigned char* name = raptor_xml_element_get_name(xml_element)->local_name;
#endif
  raptor_rss_element* rss_element;
  size_t cdata_len = 0;
  unsigned char* cdata = NULL;

  rss_element = (raptor_rss_element*)xml_element->user_data;

  rdf_parser = (raptor_parser*)user_data;
  rss_parser = (raptor_rss_parser*)rdf_parser->context;

  if(rss_element->xml_writer) {
    if(rss_element->type != RAPTOR_RSS_CONTENT_TYPE_XML) {
      raptor_xml_writer_end_element(rss_element->xml_writer, xml_element);
      goto tidy_end_element;
    }

    /* otherwise we are done making XML */
    raptor_free_iostream(rss_element->iostream);
    rss_element->iostream = NULL;
    cdata = (unsigned char*)rss_element->xml_content;
    cdata_len = rss_element->xml_content_length;
  }

  if(rss_element->sb) {
    cdata_len = raptor_stringbuffer_length(rss_element->sb);
    cdata = raptor_stringbuffer_as_string(rss_element->sb);
  }

  if(cdata) {
    raptor_uri* base_uri = NULL;
    
    base_uri = raptor_sax2_inscope_base_uri(rss_parser->sax2);

    if(rss_parser->current_block) {
      const raptor_rss_block_field_info *bfi;
      int handled = 0;
      /* in a block, maybe store the CDATA there */

      for(bfi = &raptor_rss_block_fields_info[0];
          bfi->type != RAPTOR_RSS_NONE;
          bfi++) {

        if(bfi->type != rss_parser->current_block->rss_type ||
           bfi->attribute != NULL)
          continue;

        /* Set author name from element */
        if(raptor_rss_block_set_field(rdf_parser->world, base_uri,
                                      rss_parser->current_block,
                                      bfi, (const char*)cdata)) {
          rdf_parser->failed = 1;
          return;
        }
        
        handled = 1;
        break;
      }

#ifdef RAPTOR_DEBUG
      if(!handled) {
        raptor_rss_type block_type = rss_parser->current_block->rss_type;
        RAPTOR_DEBUG3("Ignoring cdata for block %d - %s\n",
                      block_type, raptor_rss_items_info[block_type].name);
      }
#endif
      rss_parser->current_block = NULL;
      goto do_end_element;
    }

    if(rss_parser->current_type == RAPTOR_RSS_NONE ||
       (rss_parser->current_field == RAPTOR_RSS_FIELD_NONE ||
        rss_parser->current_field == RAPTOR_RSS_FIELD_UNKNOWN)) {
      unsigned char *p = cdata;
      size_t i;
      for(i = cdata_len; i > 0 && *p; i--) {
        if(!isspace(*p))
          break;
        p++;
      }
      if(i > 0 && *p) {
        RAPTOR_DEBUG4("IGNORING non-whitespace text '%s' inside type %s, field %s\n", cdata,
                      raptor_rss_items_info[rss_parser->current_type].name,
                      raptor_rss_fields_info[rss_parser->current_field].name);
      }

      goto do_end_element;
    }

    if(rss_parser->current_type >= RAPTOR_RSS_COMMON_IGNORED) {
      /* skipHours, skipDays common but IGNORED */ 
      RAPTOR_DEBUG2("Ignoring fields for type %s\n", raptor_rss_items_info[rss_parser->current_type].name);
    } else {
      raptor_rss_item* update_item = raptor_rss_get_current_item(rss_parser);
      raptor_rss_field* field = raptor_rss_new_field(rdf_parser->world);

      /* if value is always an uri, make it so */
      if(raptor_rss_fields_info[rss_parser->current_field].flags & 
         RAPTOR_RSS_INFO_FLAG_URI_VALUE) {
        RAPTOR_DEBUG4("Added URI %s to field %s of type %s\n", cdata, raptor_rss_fields_info[rss_parser->current_field].name, raptor_rss_items_info[rss_parser->current_type].name);
        field->uri = raptor_new_uri_relative_to_base(rdf_parser->world, base_uri, cdata);
      } else {
        RAPTOR_DEBUG4("Added text '%s' to field %s of type %s\n", cdata, raptor_rss_fields_info[rss_parser->current_field].name, raptor_rss_items_info[rss_parser->current_type].name);
        field->uri = NULL;
        field->value = RAPTOR_MALLOC(unsigned char*, cdata_len + 1);
        if(!field->value) {
          rdf_parser->failed = 1;
          return;
        }
        
        memcpy(field->value, cdata, cdata_len);
        field->value[cdata_len] = '\0';
      }

      RAPTOR_DEBUG1("fa3 - ");
      raptor_rss_item_add_field(update_item, rss_parser->current_field, field);
    }
  } /* end if contained cdata */

  if(raptor_xml_element_is_empty(xml_element)) {
    /* Empty element, so consider adding one of the attributes as
     * literal or URI content
     */
    if(rss_parser->current_type >= RAPTOR_RSS_COMMON_IGNORED) {
      /* skipHours, skipDays common but IGNORED */ 
      RAPTOR_DEBUG3("Ignoring empty element %s for type %s\n", name, raptor_rss_items_info[rss_parser->current_type].name);
    } else if(rss_element->uri) {
      raptor_rss_item* update_item = raptor_rss_get_current_item(rss_parser);
      raptor_rss_field* field = raptor_rss_new_field(rdf_parser->world);

      if(rss_parser->current_field == RAPTOR_RSS_FIELD_UNKNOWN) {
        RAPTOR_DEBUG2("Cannot add URI from alternate attribute to type %s unknown field\n", raptor_rss_items_info[rss_parser->current_type].name);
        raptor_rss_field_free(field);
      } else {
        RAPTOR_DEBUG3("Added URI to field %s of type %s\n", raptor_rss_fields_info[rss_parser->current_field].name, raptor_rss_items_info[rss_parser->current_type].name);
        field->uri = rss_element->uri;
        rss_element->uri = NULL;
        RAPTOR_DEBUG1("fa2 - ");
        raptor_rss_item_add_field(update_item, rss_parser->current_field, field);
      }
    }

  }

 do_end_element:
  if(rss_parser->current_type != RAPTOR_RSS_NONE) {
    if(rss_parser->current_field != RAPTOR_RSS_FIELD_NONE) {
      RAPTOR_DEBUG3("Ending element %s field %s\n", name, raptor_rss_fields_info[rss_parser->current_field].name);
      rss_parser->current_field =  RAPTOR_RSS_FIELD_NONE;
    } else {
      RAPTOR_DEBUG3("Ending element %s type %s\n", name, raptor_rss_items_info[rss_parser->current_type].name);
      if(rss_parser->prev_type != RAPTOR_RSS_NONE) {
        rss_parser->current_type = rss_parser->prev_type;
        rss_parser->prev_type = RAPTOR_RSS_NONE;
        RAPTOR_DEBUG3("Returning to type %d - %s\n", rss_parser->current_type, raptor_rss_items_info[rss_parser->current_type].name);
      } else
        rss_parser->current_type = RAPTOR_RSS_NONE;
    }
  }

  if(rss_parser->current_block) {
#ifdef RAPTOR_DEBUG
    raptor_rss_type block_type = rss_parser->current_block->rss_type;
    RAPTOR_DEBUG3("Ending current block %d - %s\n",
                  block_type, raptor_rss_items_info[block_type].name);
#endif
    rss_parser->current_block = NULL;
  }


 tidy_end_element:

  if(rss_element)
    raptor_free_rss_element(rss_element);

}
