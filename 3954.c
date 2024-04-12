xmlXPathCanRewriteDosExpression(xmlChar *expr)
{
    if (expr == NULL)
	return(0);
    do {
        if ((*expr == '/') && (*(++expr) == '/'))
	    return(1);
    } while (*expr++);
    return(0);
}
