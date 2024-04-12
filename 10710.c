raptor_libxml_error_common(void* user_data, const char *msg, va_list args, 
                           const char *prefix, int is_fatal)
{
  raptor_sax2* sax2 = NULL;
  int prefix_length = RAPTOR_BAD_CAST(int, strlen(prefix));
  int length;
  char *nmsg;
  int msg_len;
  raptor_world* world = NULL;
  raptor_locator* locator = NULL;

  if(user_data) {
    /* Work around libxml2 bug - sometimes the sax2->error
     * returns a user_data, sometimes the userdata
     */
    if(((raptor_sax2*)user_data)->magic == RAPTOR_LIBXML_MAGIC)
      sax2 = (raptor_sax2*)user_data;
    else
      /* user_data is not userData */
      sax2 = (raptor_sax2*)((xmlParserCtxtPtr)user_data)->userData;
  }

  if(sax2) {
    world = sax2->world;
    locator = sax2->locator;
    
    if(locator)
      raptor_libxml_update_document_locator(sax2, sax2->locator);
  }

  msg_len = RAPTOR_BAD_CAST(int, strlen(msg));
  length = prefix_length + msg_len + 1;
  nmsg = RAPTOR_MALLOC(char*, length);
  if(nmsg) {
    memcpy(nmsg, prefix, prefix_length); /* Do not copy NUL */
    memcpy(nmsg + prefix_length, msg, msg_len + 1); /* Copy NUL */
    if(nmsg[length-1] == '\n')
      nmsg[length-1]='\0';
  }

  if(is_fatal)
    raptor_log_error_varargs(world,
                             RAPTOR_LOG_LEVEL_FATAL,
                             locator, 
                             nmsg ? nmsg : msg, 
                             args);
  else
    raptor_log_error_varargs(world,
                             RAPTOR_LOG_LEVEL_ERROR,
                             locator, 
                             nmsg ? nmsg : msg, 
                             args);
  
  if(nmsg)
    RAPTOR_FREE(char*, nmsg);
}
