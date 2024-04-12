xmlXPtrEvalRangePredicate(xmlXPathParserContextPtr ctxt) {
    const xmlChar *cur;
    xmlXPathObjectPtr res;
    xmlXPathObjectPtr obj, tmp;
    xmlLocationSetPtr newset = NULL;
    xmlLocationSetPtr oldset;
    int i;

    if (ctxt == NULL) return;

    SKIP_BLANKS;
    if (CUR != '[') {
	XP_ERROR(XPATH_INVALID_PREDICATE_ERROR);
    }
    NEXT;
    SKIP_BLANKS;

    /*
     * Extract the old set, and then evaluate the result of the
     * expression for all the element in the set. use it to grow
     * up a new set.
     */
    CHECK_TYPE(XPATH_LOCATIONSET);
    obj = valuePop(ctxt);
    oldset = obj->user;
    ctxt->context->node = NULL;

    if ((oldset == NULL) || (oldset->locNr == 0)) {
	ctxt->context->contextSize = 0;
	ctxt->context->proximityPosition = 0;
	xmlXPathEvalExpr(ctxt);
	res = valuePop(ctxt);
	if (res != NULL)
	    xmlXPathFreeObject(res);
	valuePush(ctxt, obj);
	CHECK_ERROR;
    } else {
	/*
	 * Save the expression pointer since we will have to evaluate
	 * it multiple times. Initialize the new set.
	 */
        cur = ctxt->cur;
	newset = xmlXPtrLocationSetCreate(NULL);
	
        for (i = 0; i < oldset->locNr; i++) {
	    ctxt->cur = cur;

	    /*
	     * Run the evaluation with a node list made of a single item
	     * in the nodeset.
	     */
	    ctxt->context->node = oldset->locTab[i]->user;
	    tmp = xmlXPathNewNodeSet(ctxt->context->node);
	    valuePush(ctxt, tmp);
	    ctxt->context->contextSize = oldset->locNr;
	    ctxt->context->proximityPosition = i + 1;

	    xmlXPathEvalExpr(ctxt);
	    CHECK_ERROR;

	    /*
	     * The result of the evaluation need to be tested to
	     * decided whether the filter succeeded or not
	     */
	    res = valuePop(ctxt);
	    if (xmlXPathEvaluatePredicateResult(ctxt, res)) {
	        xmlXPtrLocationSetAdd(newset,
			xmlXPathObjectCopy(oldset->locTab[i]));
	    }

	    /*
	     * Cleanup
	     */
	    if (res != NULL)
		xmlXPathFreeObject(res);
	    if (ctxt->value == tmp) {
		res = valuePop(ctxt);
		xmlXPathFreeObject(res);
	    }
	    
	    ctxt->context->node = NULL;
	}

	/*
	 * The result is used as the new evaluation set.
	 */
	xmlXPathFreeObject(obj);
	ctxt->context->node = NULL;
	ctxt->context->contextSize = -1;
	ctxt->context->proximityPosition = -1;
	valuePush(ctxt, xmlXPtrWrapLocationSet(newset));
    }
    if (CUR != ']') {
	XP_ERROR(XPATH_INVALID_PREDICATE_ERROR);
    }

    NEXT;
    SKIP_BLANKS;
}
