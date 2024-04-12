static int spacePop(xmlParserCtxtPtr ctxt) {
 int ret;
 if (ctxt->spaceNr <= 0) return(0);
    ctxt->spaceNr--;
 if (ctxt->spaceNr > 0)
	ctxt->space = &ctxt->spaceTab[ctxt->spaceNr - 1];
 else
        ctxt->space = &ctxt->spaceTab[0];
    ret = ctxt->spaceTab[ctxt->spaceNr];
    ctxt->spaceTab[ctxt->spaceNr] = -1;
 return(ret);
}
