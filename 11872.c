xmlFatalErrMsg(xmlParserCtxtPtr ctxt, xmlParserErrors error,
 const char *msg)
{
 if ((ctxt != NULL) && (ctxt->disableSAX != 0) &&
 (ctxt->instate == XML_PARSER_EOF))
 return;
 if (ctxt != NULL)
	ctxt->errNo = error;
    __xmlRaiseError(NULL, NULL, NULL, ctxt, NULL, XML_FROM_PARSER, error,
                    XML_ERR_FATAL, NULL, 0, NULL, NULL, NULL, 0, 0, "%s", msg);
 if (ctxt != NULL) {
	ctxt->wellFormed = 0;
 if (ctxt->recovery == 0)
	    ctxt->disableSAX = 1;
 }
}
