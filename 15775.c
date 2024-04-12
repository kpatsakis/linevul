xmlCreateDocParserCtxt(const xmlChar *cur) {
    int len;

    if (cur == NULL)
	return(NULL);
    len = xmlStrlen(cur);
    return(xmlCreateMemoryParserCtxt((const char *)cur, len));
}
