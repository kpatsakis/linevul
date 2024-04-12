xmlPopInput(xmlParserCtxtPtr ctxt) {
 if ((ctxt == NULL) || (ctxt->inputNr <= 1)) return(0);
 if (xmlParserDebugEntities)
	xmlGenericError(xmlGenericErrorContext,
 "Popping input %d\n", ctxt->inputNr);
    xmlFreeInputStream(inputPop(ctxt));
 if ((*ctxt->input->cur == 0) &&
 (xmlParserInputGrow(ctxt->input, INPUT_CHUNK) <= 0))
 return(xmlPopInput(ctxt));
 return(CUR);
}
