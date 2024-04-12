xsltParseContentError(xsltStylesheetPtr style,
		       xmlNodePtr node)
{
    if ((style == NULL) || (node == NULL))
	return;

    if (IS_XSLT_ELEM(node))
	xsltTransformError(NULL, style, node,
	    "The XSLT-element '%s' is not allowed at this position.\n",
	    node->name);
    else
	xsltTransformError(NULL, style, node,
	    "The element '%s' is not allowed at this position.\n",
	    node->name);
    style->errors++;
}
