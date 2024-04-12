raptor_turtle_writer_reference(raptor_turtle_writer* turtle_writer, 
                               raptor_uri* uri)
{
  unsigned char* uri_str;
  size_t length;
  
  uri_str = raptor_uri_to_relative_counted_uri_string(turtle_writer->base_uri, uri, &length);

  raptor_iostream_write_byte('<', turtle_writer->iostr);
  if(uri_str)
    raptor_string_ntriples_write(uri_str, length, '>', turtle_writer->iostr);
  raptor_iostream_write_byte('>', turtle_writer->iostr);

  RAPTOR_FREE(char*, uri_str);
}
