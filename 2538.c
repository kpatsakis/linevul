xmlXPathCompRelationalExpr(xmlXPathParserContextPtr ctxt) {
    xmlXPathCompAdditiveExpr(ctxt);
    CHECK_ERROR;
    SKIP_BLANKS;
    while ((CUR == '<') ||
           (CUR == '>') ||
           ((CUR == '<') && (NXT(1) == '=')) ||
           ((CUR == '>') && (NXT(1) == '='))) {
	int inf, strict;
	int op1 = ctxt->comp->last;

        if (CUR == '<') inf = 1;
	else inf = 0;
	if (NXT(1) == '=') strict = 0;
	else strict = 1;
	NEXT;
	if (!strict) NEXT;
	SKIP_BLANKS;
        xmlXPathCompAdditiveExpr(ctxt);
	CHECK_ERROR;
	PUSH_BINARY_EXPR(XPATH_OP_CMP, op1, ctxt->comp->last, inf, strict);
	SKIP_BLANKS;
    }
}
