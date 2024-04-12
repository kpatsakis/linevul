xmlCtxtGrowAttrs(xmlParserCtxtPtr ctxt, int nr) {
    const xmlChar **atts;
    int *attallocs;
    int maxatts;

    if (ctxt->atts == NULL) {
	maxatts = 55; /* allow for 10 attrs by default */
	atts = (const xmlChar **)
	       xmlMalloc(maxatts * sizeof(xmlChar *));
	if (atts == NULL) goto mem_error;
	ctxt->atts = atts;
	attallocs = (int *) xmlMalloc((maxatts / 5) * sizeof(int));
	if (attallocs == NULL) goto mem_error;
	ctxt->attallocs = attallocs;
	ctxt->maxatts = maxatts;
    } else if (nr + 5 > ctxt->maxatts) {
	maxatts = (nr + 5) * 2;
	atts = (const xmlChar **) xmlRealloc((void *) ctxt->atts,
				     maxatts * sizeof(const xmlChar *));
	if (atts == NULL) goto mem_error;
	ctxt->atts = atts;
	attallocs = (int *) xmlRealloc((void *) ctxt->attallocs,
	                             (maxatts / 5) * sizeof(int));
	if (attallocs == NULL) goto mem_error;
	ctxt->attallocs = attallocs;
	ctxt->maxatts = maxatts;
    }
    return(ctxt->maxatts);
mem_error:
    xmlErrMemory(ctxt, NULL);
    return(-1);
}
