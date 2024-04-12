exsltFuncResultElem (xsltTransformContextPtr ctxt,
	             xmlNodePtr node ATTRIBUTE_UNUSED, xmlNodePtr inst,
		     exsltFuncResultPreComp *comp) {
    exsltFuncData *data;
    xmlXPathObjectPtr ret;


    /* It is an error if instantiating the content of the
     * func:function element results in the instantiation of more than
     * one func:result elements.
     */
    data = (exsltFuncData *) xsltGetExtData (ctxt, EXSLT_FUNCTIONS_NAMESPACE);
    if (data == NULL) {
	xsltGenericError(xsltGenericErrorContext,
			 "exsltFuncReturnElem: data == NULL\n");
	return;
    }
    if (data->result != NULL) {
	xsltGenericError(xsltGenericErrorContext,
			 "func:result already instanciated\n");
	data->error = 1;
	return;
    }
    /*
     * Processing
     */
    if (comp->select != NULL) {
	xmlNsPtr *oldXPNsList;
	int oldXPNsNr;
	xmlNodePtr oldXPContextNode;
	/* If the func:result element has a select attribute, then the
	 * value of the attribute must be an expression and the
	 * returned value is the object that results from evaluating
	 * the expression. In this case, the content must be empty.
	 */
	if (inst->children != NULL) {
	    xsltGenericError(xsltGenericErrorContext,
			     "func:result content must be empty if"
			     " the function has a select attribute\n");
	    data->error = 1;
	    return;
	}
	oldXPNsList = ctxt->xpathCtxt->namespaces;
	oldXPNsNr = ctxt->xpathCtxt->nsNr;
	oldXPContextNode = ctxt->xpathCtxt->node;

	ctxt->xpathCtxt->namespaces = comp->nsList;
	ctxt->xpathCtxt->nsNr = comp->nsNr;

	ret = xmlXPathCompiledEval(comp->select, ctxt->xpathCtxt);

	ctxt->xpathCtxt->node = oldXPContextNode;
	ctxt->xpathCtxt->nsNr = oldXPNsNr;
	ctxt->xpathCtxt->namespaces = oldXPNsList;

	if (ret == NULL) {
	    xsltGenericError(xsltGenericErrorContext,
			     "exsltFuncResultElem: ret == NULL\n");
	    return;
	}
	/*
	* Mark it as a function result in order to avoid garbage
	* collecting of tree fragments before the function exits.
	*/
	xsltExtensionInstructionResultRegister(ctxt, ret);
    } else if (inst->children != NULL) {
	/* If the func:result element does not have a select attribute
	 * and has non-empty content (i.e. the func:result element has
	 * one or more child nodes), then the content of the
	 * func:result element specifies the value.
	 */
	xmlNodePtr oldInsert;
	xmlDocPtr container;

	container = xsltCreateRVT(ctxt);
	if (container == NULL) {
	    xsltGenericError(xsltGenericErrorContext,
			     "exsltFuncResultElem: out of memory\n");
	    data->error = 1;
	    return;
	}
	xsltRegisterLocalRVT(ctxt, container);

	oldInsert = ctxt->insert;
	ctxt->insert = (xmlNodePtr) container;
	xsltApplyOneTemplate (ctxt, ctxt->xpathCtxt->node,
			      inst->children, NULL, NULL);
	ctxt->insert = oldInsert;

	ret = xmlXPathNewValueTree((xmlNodePtr) container);
	if (ret == NULL) {
	    xsltGenericError(xsltGenericErrorContext,
			     "exsltFuncResultElem: ret == NULL\n");
	    data->error = 1;
	} else {
	    ret->boolval = 0; /* Freeing is not handled there anymore */
	    /*
	    * Mark it as a function result in order to avoid garbage
	    * collecting of tree fragments before the function exits.
	    */
	    xsltExtensionInstructionResultRegister(ctxt, ret);
	}
    } else {
	/* If the func:result element has empty content and does not
	 * have a select attribute, then the returned value is an
	 * empty string.
	 */
	ret = xmlXPathNewCString("");
    }
    data->result = ret;
}
