load_xpath_expr (xmlDocPtr parent_doc, const char* filename) {
    xmlXPathObjectPtr xpath;
    xmlDocPtr doc;
    xmlChar *expr;
    xmlXPathContextPtr ctx;
    xmlNodePtr node;
    xmlNsPtr ns;

    /*
     * load XPath expr as a file
     */
    xmlLoadExtDtdDefaultValue = XML_DETECT_IDS | XML_COMPLETE_ATTRS;
    xmlSubstituteEntitiesDefault(1);

    doc = xmlReadFile(filename, NULL, XML_PARSE_DTDATTR | XML_PARSE_NOENT);
    if (doc == NULL) {
	fprintf(stderr, "Error: unable to parse file \"%s\"\n", filename);
	return(NULL);
    }

    /*
     * Check the document is of the right kind
     */
    if(xmlDocGetRootElement(doc) == NULL) {
        fprintf(stderr,"Error: empty document for file \"%s\"\n", filename);
	xmlFreeDoc(doc);
	return(NULL);
    }

    node = doc->children;
    while(node != NULL && !xmlStrEqual(node->name, (const xmlChar *)"XPath")) {
	node = node->next;
    }

    if(node == NULL) {
        fprintf(stderr,"Error: XPath element expected in the file  \"%s\"\n", filename);
	xmlFreeDoc(doc);
	return(NULL);
    }

    expr = xmlNodeGetContent(node);
    if(expr == NULL) {
        fprintf(stderr,"Error: XPath content element is NULL \"%s\"\n", filename);
	xmlFreeDoc(doc);
	return(NULL);
    }

    ctx = xmlXPathNewContext(parent_doc);
    if(ctx == NULL) {
        fprintf(stderr,"Error: unable to create new context\n");
        xmlFree(expr);
        xmlFreeDoc(doc);
        return(NULL);
    }

    /*
     * Register namespaces
     */
    ns = node->nsDef;
    while(ns != NULL) {
	if(xmlXPathRegisterNs(ctx, ns->prefix, ns->href) != 0) {
	    fprintf(stderr,"Error: unable to register NS with prefix=\"%s\" and href=\"%s\"\n", ns->prefix, ns->href);
    xmlFree(expr);
	    xmlXPathFreeContext(ctx);
	    xmlFreeDoc(doc);
	    return(NULL);
	}
	ns = ns->next;
    }

    /*
     * Evaluate xpath
     */
    xpath = xmlXPathEvalExpression(expr, ctx);
    if(xpath == NULL) {
        fprintf(stderr,"Error: unable to evaluate xpath expression\n");
xmlFree(expr);
        xmlXPathFreeContext(ctx);
        xmlFreeDoc(doc);
        return(NULL);
    }

    /* print_xpath_nodes(xpath->nodesetval); */

    xmlFree(expr);
    xmlXPathFreeContext(ctx);
    xmlFreeDoc(doc);
    return(xpath);
}
