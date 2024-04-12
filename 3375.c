saxParseTest(const char *filename, const char *result,
             const char *err ATTRIBUTE_UNUSED,
             int options) {
    int ret;
    char *temp;

    nb_tests++;
    temp = resultFilename(filename, "", ".res");
    if (temp == NULL) {
        fprintf(stderr, "out of memory\n");
        fatalError();
    }
    SAXdebug = fopen(temp, "wb");
    if (SAXdebug == NULL) {
        fprintf(stderr, "Failed to write to %s\n", temp);
	free(temp);
	return(-1);
    }

    /* for SAX we really want the callbacks though the context handlers */
    xmlSetStructuredErrorFunc(NULL, NULL);
    xmlSetGenericErrorFunc(NULL, testErrorHandler);

#ifdef LIBXML_HTML_ENABLED
    if (options & XML_PARSE_HTML) {
	htmlSAXParseFile(filename, NULL, emptySAXHandler, NULL);
	ret = 0;
    } else
#endif
    ret = xmlSAXUserParseFile(emptySAXHandler, NULL, filename);
    if (ret == XML_WAR_UNDECLARED_ENTITY) {
        fprintf(SAXdebug, "xmlSAXUserParseFile returned error %d\n", ret);
        ret = 0;
    }
    if (ret != 0) {
        fprintf(stderr, "Failed to parse %s\n", filename);
	ret = 1;
	goto done;
    }
#ifdef LIBXML_HTML_ENABLED
    if (options & XML_PARSE_HTML) {
	htmlSAXParseFile(filename, NULL, debugHTMLSAXHandler, NULL);
	ret = 0;
    } else
#endif
    if (options & XML_PARSE_SAX1) {
	ret = xmlSAXUserParseFile(debugSAXHandler, NULL, filename);
    } else {
	ret = xmlSAXUserParseFile(debugSAX2Handler, NULL, filename);
    }
    if (ret == XML_WAR_UNDECLARED_ENTITY) {
        fprintf(SAXdebug, "xmlSAXUserParseFile returned error %d\n", ret);
        ret = 0;
    }
    fclose(SAXdebug);
    if (compareFiles(temp, result)) {
        fprintf(stderr, "Got a difference for %s\n", filename);
        ret = 1;
    }

done:
    if (temp != NULL) {
        unlink(temp);
        free(temp);
    }

    /* switch back to structured error handling */
    xmlSetGenericErrorFunc(NULL, NULL);
    xmlSetStructuredErrorFunc(NULL, testStructuredErrorHandler);

    return(ret);
}
