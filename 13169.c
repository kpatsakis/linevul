namePop(xmlParserCtxtPtr ctxt)
{
 const xmlChar *ret;

 if ((ctxt == NULL) || (ctxt->nameNr <= 0))
 return (NULL);
    ctxt->nameNr--;
 if (ctxt->nameNr > 0)
        ctxt->name = ctxt->nameTab[ctxt->nameNr - 1];
 else
        ctxt->name = NULL;
    ret = ctxt->nameTab[ctxt->nameNr];
    ctxt->nameTab[ctxt->nameNr] = NULL;
 return (ret);
}
