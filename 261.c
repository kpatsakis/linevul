xsltBuildVariable(xsltTransformContextPtr ctxt,
		  xsltStylePreCompPtr castedComp,
		  xmlNodePtr tree)
{
#ifdef XSLT_REFACTORED
    xsltStyleBasicItemVariablePtr comp =
	(xsltStyleBasicItemVariablePtr) castedComp;
#else
    xsltStylePreCompPtr comp = castedComp;
#endif
    xsltStackElemPtr elem;

#ifdef WITH_XSLT_DEBUG_VARIABLE
    XSLT_TRACE(ctxt,XSLT_TRACE_VARIABLES,xsltGenericDebug(xsltGenericDebugContext,
		     "Building variable %s", comp->name));
    if (comp->select != NULL)
	XSLT_TRACE(ctxt,XSLT_TRACE_VARIABLES,xsltGenericDebug(xsltGenericDebugContext,
			 " select %s", comp->select));
    XSLT_TRACE(ctxt,XSLT_TRACE_VARIABLES,xsltGenericDebug(xsltGenericDebugContext, "\n"));
#endif

    elem = xsltNewStackElem(ctxt);
    if (elem == NULL)
	return(NULL);
    elem->comp = (xsltStylePreCompPtr) comp;
    elem->name = comp->name;
    elem->select = comp->select;
    elem->nameURI = comp->ns;
    elem->tree = tree;
    elem->value = xsltEvalVariable(ctxt, elem,
	(xsltStylePreCompPtr) comp);
    if (elem->value != NULL)
	elem->computed = 1;
    return(elem);
}
