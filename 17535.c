xsltFreeCtxtExts(xsltTransformContextPtr ctxt)
{
    if (ctxt->extElements != NULL)
        xmlHashFree(ctxt->extElements, NULL);
    if (ctxt->extFunctions != NULL)
        xmlHashFree(ctxt->extFunctions, NULL);
}
