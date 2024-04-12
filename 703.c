xmlCtxtUseOptions(xmlParserCtxtPtr ctxt, int options)
{
   return(xmlCtxtUseOptionsInternal(ctxt, options, NULL));
}
