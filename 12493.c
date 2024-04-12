xsltCompilerVarInfoPop(xsltCompilerCtxtPtr cctxt)
{

    while ((cctxt->ivar != NULL) &&
	(cctxt->ivar->depth > cctxt->depth))
    {
	cctxt->ivar = cctxt->ivar->prev;
    }
}
