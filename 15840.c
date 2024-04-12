xsltFreeGlobalVariables(xsltTransformContextPtr ctxt) {
    xmlHashFree(ctxt->globalVars, (xmlHashDeallocator) xsltFreeStackElem);
}
