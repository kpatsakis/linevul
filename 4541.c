xsltRegisterPersistRVT(xsltTransformContextPtr ctxt, xmlDocPtr RVT)
{
    if ((ctxt == NULL) || (RVT == NULL)) return(-1);

    RVT->next = (xmlNodePtr) ctxt->persistRVT;
    if (ctxt->persistRVT != NULL)
	ctxt->persistRVT->prev = (xmlNodePtr) RVT;
    ctxt->persistRVT = RVT;
    return(0);
}
