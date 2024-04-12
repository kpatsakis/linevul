xmlParseVersionNum(xmlParserCtxtPtr ctxt) {
    xmlChar *buf = NULL;
    int len = 0;
    int size = 10;
    xmlChar cur;

    buf = (xmlChar *) xmlMallocAtomic(size * sizeof(xmlChar));
    if (buf == NULL) {
	xmlErrMemory(ctxt, NULL);
	return(NULL);
    }
    cur = CUR;
    if (!((cur >= '0') && (cur <= '9'))) {
	xmlFree(buf);
	return(NULL);
    }
    buf[len++] = cur;
    NEXT;
    cur=CUR;
    if (cur != '.') {
	xmlFree(buf);
	return(NULL);
    }
    buf[len++] = cur;
    NEXT;
    cur=CUR;
    while ((cur >= '0') && (cur <= '9')) {
	if (len + 1 >= size) {
	    xmlChar *tmp;

	    size *= 2;
	    tmp = (xmlChar *) xmlRealloc(buf, size * sizeof(xmlChar));
	    if (tmp == NULL) {
	        xmlFree(buf);
		xmlErrMemory(ctxt, NULL);
		return(NULL);
	    }
	    buf = tmp;
	}
	buf[len++] = cur;
	NEXT;
	cur=CUR;
    }
    buf[len] = 0;
    return(buf);
}
