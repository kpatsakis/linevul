xmlXPathNameFunction(xmlXPathParserContextPtr ctxt, int nargs)
{
    xmlXPathObjectPtr cur;

    if (nargs == 0) {
	valuePush(ctxt, xmlXPathCacheNewNodeSet(ctxt->context,
	    ctxt->context->node));
        nargs = 1;
    }

    CHECK_ARITY(1);
    if ((ctxt->value == NULL) ||
        ((ctxt->value->type != XPATH_NODESET) &&
         (ctxt->value->type != XPATH_XSLT_TREE)))
        XP_ERROR(XPATH_INVALID_TYPE);
    cur = valuePop(ctxt);

    if ((cur->nodesetval == NULL) || (cur->nodesetval->nodeNr == 0)) {
        valuePush(ctxt, xmlXPathCacheNewCString(ctxt->context, ""));
    } else {
        int i = 0;              /* Should be first in document order !!!!! */

        switch (cur->nodesetval->nodeTab[i]->type) {
            case XML_ELEMENT_NODE:
            case XML_ATTRIBUTE_NODE:
		if (cur->nodesetval->nodeTab[i]->name[0] == ' ')
		    valuePush(ctxt,
			xmlXPathCacheNewCString(ctxt->context, ""));
		else if ((cur->nodesetval->nodeTab[i]->ns == NULL) ||
                         (cur->nodesetval->nodeTab[i]->ns->prefix == NULL)) {
		    valuePush(ctxt,
		        xmlXPathCacheNewString(ctxt->context,
			    cur->nodesetval->nodeTab[i]->name));
		} else {
		    xmlChar *fullname;

		    fullname = xmlBuildQName(cur->nodesetval->nodeTab[i]->name,
				     cur->nodesetval->nodeTab[i]->ns->prefix,
				     NULL, 0);
		    if (fullname == cur->nodesetval->nodeTab[i]->name)
			fullname = xmlStrdup(cur->nodesetval->nodeTab[i]->name);
		    if (fullname == NULL) {
			XP_ERROR(XPATH_MEMORY_ERROR);
		    }
		    valuePush(ctxt, xmlXPathCacheWrapString(
			ctxt->context, fullname));
                }
                break;
            default:
		valuePush(ctxt, xmlXPathCacheNewNodeSet(ctxt->context,
		    cur->nodesetval->nodeTab[i]));
                xmlXPathLocalNameFunction(ctxt, 1);
        }
    }
    xmlXPathReleaseObject(ctxt->context, cur);
}
