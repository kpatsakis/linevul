xmlParseExternalEntity(xmlDocPtr doc, xmlSAXHandlerPtr sax, void *user_data,
	  int depth, const xmlChar *URL, const xmlChar *ID, xmlNodePtr *lst) {
    return(xmlParseExternalEntityPrivate(doc, NULL, sax, user_data, depth, URL,
		                       ID, lst));
}
