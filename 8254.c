xmlXPathEqualNodeSetString(xmlXPathObjectPtr arg, const xmlChar * str, int neq)
{
    int i;
    xmlNodeSetPtr ns;
    xmlChar *str2;
    unsigned int hash;

    if ((str == NULL) || (arg == NULL) ||
        ((arg->type != XPATH_NODESET) && (arg->type != XPATH_XSLT_TREE)))
        return (0);
    ns = arg->nodesetval;
    /*
     * A NULL nodeset compared with a string is always false
     * (since there is no node equal, and no node not equal)
     */
    if ((ns == NULL) || (ns->nodeNr <= 0) )
        return (0);
    hash = xmlXPathStringHash(str);
    for (i = 0; i < ns->nodeNr; i++) {
        if (xmlXPathNodeValHash(ns->nodeTab[i]) == hash) {
            str2 = xmlNodeGetContent(ns->nodeTab[i]);
            if ((str2 != NULL) && (xmlStrEqual(str, str2))) {
                xmlFree(str2);
		if (neq)
		    continue;
                return (1);
	    } else if ((str2 == NULL) && (xmlStrEqual(str, BAD_CAST ""))) {
		if (neq)
		    continue;
                return (1);
            } else if (neq) {
		if (str2 != NULL)
		    xmlFree(str2);
		return (1);
	    }
            if (str2 != NULL)
                xmlFree(str2);
        } else if (neq)
	    return (1);
    }
    return (0);
}
