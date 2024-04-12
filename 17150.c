xmlXPtrHereFunction(xmlXPathParserContextPtr ctxt, int nargs) {
    CHECK_ARITY(0);

    if (ctxt->context->here == NULL)
	XP_ERROR(XPTR_SYNTAX_ERROR);
    
    valuePush(ctxt, xmlXPtrNewLocationSetNodes(ctxt->context->here, NULL));
}
