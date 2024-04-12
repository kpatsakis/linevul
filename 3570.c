xpath_search(xmlNode * xml_top, const char *path)
{
    xmlDocPtr doc = NULL;
    xmlXPathObjectPtr xpathObj = NULL;
    xmlXPathContextPtr xpathCtx = NULL;
    const xmlChar *xpathExpr = (const xmlChar *)path;

    CRM_CHECK(path != NULL, return NULL);
    CRM_CHECK(xml_top != NULL, return NULL);
    CRM_CHECK(strlen(path) > 0, return NULL);

    doc = getDocPtr(xml_top);

    xpathCtx = xmlXPathNewContext(doc);
    CRM_ASSERT(xpathCtx != NULL);

    xpathObj = xmlXPathEvalExpression(xpathExpr, xpathCtx);
    xmlXPathFreeContext(xpathCtx);
    return xpathObj;
}
