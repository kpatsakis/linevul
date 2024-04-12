raptor_option_get_option_area_for_domain(raptor_domain domain)
{
  raptor_option_area area = RAPTOR_OPTION_AREA_NONE;

  if(domain == RAPTOR_DOMAIN_PARSER) 
    area = RAPTOR_OPTION_AREA_PARSER;
  else if(domain == RAPTOR_DOMAIN_SERIALIZER)
    area = RAPTOR_OPTION_AREA_SERIALIZER;
  else if(domain == RAPTOR_DOMAIN_SAX2)
    area = RAPTOR_OPTION_AREA_SAX2;
  else if(domain == RAPTOR_DOMAIN_XML_WRITER)
    area = RAPTOR_OPTION_AREA_XML_WRITER;
  else if(domain == RAPTOR_DOMAIN_TURTLE_WRITER)
    area = RAPTOR_OPTION_AREA_TURTLE_WRITER;

  return area;
}
