raptor_libxml_validation_warning(void* user_data, const char *msg, ...) 
{
  va_list args;
  raptor_sax2* sax2 = (raptor_sax2*)user_data;
  int prefix_length = RAPTOR_GOOD_CAST(int, strlen(xml_validation_warning_prefix));
  int length;
  char *nmsg;
  int msg_len;
  
  va_start(args, msg);

  raptor_libxml_update_document_locator(sax2, sax2->locator);

  msg_len = RAPTOR_BAD_CAST(int, strlen(msg));
  length = prefix_length + msg_len + 1;
  nmsg = RAPTOR_MALLOC(char*, length);
  if(nmsg) {
    memcpy(nmsg, xml_validation_warning_prefix, prefix_length); /* Do not copy NUL */
    memcpy(nmsg + prefix_length, msg, msg_len + 1); /* Copy NUL */
    if(nmsg[length-2] == '\n')
      nmsg[length-2]='\0';
  }

  raptor_log_error_varargs(sax2->world,
                           RAPTOR_LOG_LEVEL_WARN,
                           sax2->locator, 
                           nmsg ? nmsg : msg, 
                           args);
  if(nmsg)
    RAPTOR_FREE(char*, nmsg);
  va_end(args);
}
