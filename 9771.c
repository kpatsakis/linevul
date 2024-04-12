exsltFuncNewFunctionData (void) {
    exsltFuncFunctionData *ret;

    ret = (exsltFuncFunctionData *) xmlMalloc (sizeof(exsltFuncFunctionData));
    if (ret == NULL) {
	xsltGenericError(xsltGenericErrorContext,
			 "exsltFuncNewFunctionData: not enough memory\n");
	return (NULL);
    }
    memset(ret, 0, sizeof(exsltFuncFunctionData));

    ret->nargs = 0;
    ret->content = NULL;

    return(ret);
}
