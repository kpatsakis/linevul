exsltFuncResultComp (xsltStylesheetPtr style, xmlNodePtr inst,
		     xsltTransformFunction function) {
    xmlNodePtr test;
    xmlChar *sel;
    exsltFuncResultPreComp *ret;

    if ((style == NULL) || (inst == NULL) || (inst->type != XML_ELEMENT_NODE))
        return (NULL);

    /*
     * "Validity" checking
     */
    /* it is an error to have any following sibling elements aside
     * from the xsl:fallback element.
     */
    for (test = inst->next; test != NULL; test = test->next) {
	if (test->type != XML_ELEMENT_NODE)
	    continue;
	if (IS_XSLT_ELEM(test) && IS_XSLT_NAME(test, "fallback"))
	    continue;
	xsltGenericError(xsltGenericErrorContext,
			 "exsltFuncResultElem: only xsl:fallback is "
			 "allowed to follow func:result\n");
	style->errors++;
	return (NULL);
    }
    /* it is an error for a func:result element to not be a descendant
     * of func:function.
     * it is an error if a func:result occurs within a func:result
     * element.
     * it is an error if instanciating the content of a variable
     * binding element (i.e. xsl:variable, xsl:param) results in the
     * instanciation of a func:result element.
     */
    for (test = inst->parent; test != NULL; test = test->parent) {
	if (IS_XSLT_ELEM(test) &&
	    IS_XSLT_NAME(test, "stylesheet")) {
	    xsltGenericError(xsltGenericErrorContext,
			     "func:result element not a descendant "
			     "of a func:function\n");
	    style->errors++;
	    return (NULL);
	}
	if ((test->ns != NULL) &&
	    (xmlStrEqual(test->ns->href, EXSLT_FUNCTIONS_NAMESPACE))) {
	    if (xmlStrEqual(test->name, (const xmlChar *) "function")) {
		break;
	    }
	    if (xmlStrEqual(test->name, (const xmlChar *) "result")) {
		xsltGenericError(xsltGenericErrorContext,
				 "func:result element not allowed within"
				 " another func:result element\n");
	        style->errors++;
		return (NULL);
	    }
	}
	if (IS_XSLT_ELEM(test) &&
	    (IS_XSLT_NAME(test, "variable") ||
	     IS_XSLT_NAME(test, "param"))) {
	    xsltGenericError(xsltGenericErrorContext,
			     "func:result element not allowed within"
			     " a variable binding element\n");
            style->errors++;
	    return (NULL);
	}
    }

    /*
     * Precomputation
     */
    ret = (exsltFuncResultPreComp *)
	xmlMalloc (sizeof(exsltFuncResultPreComp));
    if (ret == NULL) {
	xsltPrintErrorContext(NULL, NULL, NULL);
        xsltGenericError(xsltGenericErrorContext,
                         "exsltFuncResultComp : malloc failed\n");
        style->errors++;
        return (NULL);
    }
    memset(ret, 0, sizeof(exsltFuncResultPreComp));

    xsltInitElemPreComp ((xsltElemPreCompPtr) ret, style, inst, function,
		 (xsltElemPreCompDeallocator) exsltFreeFuncResultPreComp);
    ret->select = NULL;

    /*
     * Precompute the select attribute
     */
    sel = xmlGetNsProp(inst, (const xmlChar *) "select", NULL);
    if (sel != NULL) {
	ret->select = xmlXPathCompile (sel);
	xmlFree(sel);
    }
    /*
     * Precompute the namespace list
     */
    ret->nsList = xmlGetNsList(inst->doc, inst);
    if (ret->nsList != NULL) {
        int i = 0;
        while (ret->nsList[i] != NULL)
	    i++;
	ret->nsNr = i;
    }
    return ((xsltElemPreCompPtr) ret);
}
