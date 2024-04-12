xmlNsErr(xmlParserCtxtPtr ctxt, xmlParserErrors error,
 const char *msg,
 const xmlChar * info1, const xmlChar * info2,
 const xmlChar * info3)
{
 if ((ctxt != NULL) && (ctxt->disableSAX != 0) &&
 (ctxt->instate == XML_PARSER_EOF))
 return;
 if (ctxt != NULL)
	ctxt->errNo = error;
    __xmlRaiseError(NULL, NULL, NULL, ctxt, NULL, XML_FROM_NAMESPACE, error,
                    XML_ERR_ERROR, NULL, 0, (const char *) info1,
 (const char *) info2, (const char *) info3, 0, 0, msg,
                    info1, info2, info3);
 if (ctxt != NULL)
	ctxt->nsWellFormed = 0;
}
