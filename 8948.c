xmlParseGetLasts(xmlParserCtxtPtr ctxt, const xmlChar **lastlt,
                 const xmlChar **lastgt) {
    const xmlChar *tmp;

    if ((ctxt == NULL) || (lastlt == NULL) || (lastgt == NULL)) {
	xmlGenericError(xmlGenericErrorContext,
		    "Internal error: xmlParseGetLasts\n");
	return;
    }
    if ((ctxt->progressive != 0) && (ctxt->inputNr == 1)) {
        tmp = ctxt->input->end;
	tmp--;
	while ((tmp >= ctxt->input->base) && (*tmp != '<')) tmp--;
	if (tmp < ctxt->input->base) {
	    *lastlt = NULL;
	    *lastgt = NULL;
	} else {
	    *lastlt = tmp;
	    tmp++;
	    while ((tmp < ctxt->input->end) && (*tmp != '>')) {
	        if (*tmp == '\'') {
		    tmp++;
		    while ((tmp < ctxt->input->end) && (*tmp != '\'')) tmp++;
		    if (tmp < ctxt->input->end) tmp++;
		} else if (*tmp == '"') {
		    tmp++;
		    while ((tmp < ctxt->input->end) && (*tmp != '"')) tmp++;
		    if (tmp < ctxt->input->end) tmp++;
		} else
		    tmp++;
	    }
	    if (tmp < ctxt->input->end)
	        *lastgt = tmp;
	    else {
	        tmp = *lastlt;
		tmp--;
		while ((tmp >= ctxt->input->base) && (*tmp != '>')) tmp--;
		if (tmp >= ctxt->input->base)
		    *lastgt = tmp;
		else
		    *lastgt = NULL;
	    }
	}
    } else {
        *lastlt = NULL;
	*lastgt = NULL;
    }
}
