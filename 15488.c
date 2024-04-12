xsltExtStyleInitTest(xsltStylesheetPtr style ATTRIBUTE_UNUSED,
                     const xmlChar * URI)
{
    if (testStyleData != NULL) {
        xsltTransformError(NULL, NULL, NULL,
                           "xsltExtInitTest: already initialized\n");
        return (NULL);
    }
    testStyleData = (void *) "test data";
    xsltGenericDebug(xsltGenericDebugContext,
                     "Registered test module : %s\n", URI);
    return (testStyleData);
}
