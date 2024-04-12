xsltRegisterExtFunction(xsltTransformContextPtr ctxt, const xmlChar * name,
                        const xmlChar * URI, xmlXPathFunction function)
{
    int ret;

    if ((ctxt == NULL) || (name == NULL) ||
        (URI == NULL) || (function == NULL))
        return (-1);
    if (ctxt->xpathCtxt != NULL) {
        xmlXPathRegisterFuncNS(ctxt->xpathCtxt, name, URI, function);
    }
    if (ctxt->extFunctions == NULL)
        ctxt->extFunctions = xmlHashCreate(10);
    if (ctxt->extFunctions == NULL)
        return (-1);

    ret = xmlHashAddEntry2(ctxt->extFunctions, name, URI,
                           XML_CAST_FPTR(function));

    return(ret);
}
