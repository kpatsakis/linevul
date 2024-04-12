xsltApplyFallbacks(xsltTransformContextPtr ctxt, xmlNodePtr node,
	           xmlNodePtr inst) {

    xmlNodePtr child;
    int ret = 0;

    if ((ctxt == NULL) || (node == NULL) || (inst == NULL) ||
	(inst->children == NULL))
	return(0);

    child = inst->children;
    while (child != NULL) {
        if ((IS_XSLT_ELEM(child)) &&
            (xmlStrEqual(child->name, BAD_CAST "fallback"))) {
#ifdef WITH_XSLT_DEBUG_PARSING
	    xsltGenericDebug(xsltGenericDebugContext,
			     "applying xsl:fallback\n");
#endif
	    ret++;
	    xsltApplySequenceConstructor(ctxt, node, child->children,
		NULL);
	}
	child = child->next;
    }
    return(ret);
}
