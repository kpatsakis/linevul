xmlXPathPositionFunction(xmlXPathParserContextPtr ctxt, int nargs) {
    CHECK_ARITY(0);
    if (ctxt->context->proximityPosition >= 0) {
	valuePush(ctxt,
	      xmlXPathCacheNewFloat(ctxt->context,
		(double) ctxt->context->proximityPosition));
#ifdef DEBUG_EXPR
	xmlGenericError(xmlGenericErrorContext, "position() : %d\n",
		ctxt->context->proximityPosition);
#endif
    } else {
	XP_ERROR(XPATH_INVALID_CTXT_POSITION);
    }
}
