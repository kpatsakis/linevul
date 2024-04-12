xsltTemplateParamsCleanup(xsltTransformContextPtr ctxt)
{
    xsltStackElemPtr param;

    for (; ctxt->varsNr > ctxt->varsBase; ctxt->varsNr--) {
	param = ctxt->varsTab[ctxt->varsNr -1];
	/*
	* Free xsl:param items.
	* xsl:with-param items will have a level of -1 or -2.
	*/
	if (param->level >= 0) {
	    xsltFreeStackElemList(param);
	}
    }
    if (ctxt->varsNr > 0)
        ctxt->vars = ctxt->varsTab[ctxt->varsNr - 1];
    else
        ctxt->vars = NULL;
}
