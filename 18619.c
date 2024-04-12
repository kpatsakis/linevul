xsltGetSAS(xsltStylesheetPtr style, const xmlChar *name, const xmlChar *ns) {
    xsltAttrElemPtr values;

    while (style != NULL) {
	values = xmlHashLookup2(style->attributeSets, name, ns);
	if (values != NULL)
	    return(values);
	style = xsltNextImport(style);
    }
    return(NULL);
 }
