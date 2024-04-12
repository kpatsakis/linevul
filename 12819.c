xsltExtStyleShutdownTest(xsltStylesheetPtr style ATTRIBUTE_UNUSED,
                         const xmlChar * URI, void *data)
{
    if (testStyleData == NULL) {
        xsltGenericError(xsltGenericErrorContext,
                         "xsltExtShutdownTest: not initialized\n");
        return;
    }
    if (data != testStyleData) {
        xsltTransformError(NULL, NULL, NULL,
                           "xsltExtShutdownTest: wrong data\n");
    }
    testStyleData = NULL;
    xsltGenericDebug(xsltGenericDebugContext,
                     "Unregistered test module : %s\n", URI);
}
