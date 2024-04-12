xmlXPathParseNCName(xmlXPathParserContextPtr ctxt) {
    const xmlChar *in;
    xmlChar *ret;
    int count = 0;

    if ((ctxt == NULL) || (ctxt->cur == NULL)) return(NULL);
    /*
     * Accelerator for simple ASCII names
     */
    in = ctxt->cur;
    if (((*in >= 0x61) && (*in <= 0x7A)) ||
	((*in >= 0x41) && (*in <= 0x5A)) ||
	(*in == '_')) {
	in++;
	while (((*in >= 0x61) && (*in <= 0x7A)) ||
	       ((*in >= 0x41) && (*in <= 0x5A)) ||
	       ((*in >= 0x30) && (*in <= 0x39)) ||
	       (*in == '_') || (*in == '.') ||
	       (*in == '-'))
	    in++;
	if ((*in == ' ') || (*in == '>') || (*in == '/') ||
            (*in == '[') || (*in == ']') || (*in == ':') ||
            (*in == '@') || (*in == '*')) {
	    count = in - ctxt->cur;
	    if (count == 0)
		return(NULL);
	    ret = xmlStrndup(ctxt->cur, count);
	    ctxt->cur = in;
	    return(ret);
	}
    }
    return(xmlXPathParseNameComplex(ctxt, 0));
}
