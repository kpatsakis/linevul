raptor_rss_parse_chunk(raptor_parser* rdf_parser, 
                       const unsigned char *s, size_t len,
                       int is_end)
{
  raptor_rss_parser* rss_parser = (raptor_rss_parser*)rdf_parser->context;
  
  if(rdf_parser->failed)
    return 1;

  raptor_sax2_parse_chunk(rss_parser->sax2, s, len, is_end);

  if(!is_end)
    return 0;

  if(rdf_parser->failed)
    return 1;

  /* turn strings into URIs, move things around if needed */
  if(raptor_rss_insert_identifiers(rdf_parser)) {
    rdf_parser->failed = 1;
    return 1;
  }
  
  /* add some new fields  */
  raptor_rss_uplift_items(rdf_parser);

  /* find out what namespaces to declare and start them */
  raptor_rss_start_namespaces(rdf_parser);
  
  /* generate the triples */
  raptor_rss_emit(rdf_parser);

  return 0;
}
