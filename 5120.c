xmlXPathCacheNewFloat(xmlXPathContextPtr ctxt, double val)
{
     if ((ctxt != NULL) && (ctxt->cache)) {
	xmlXPathContextCachePtr cache = (xmlXPathContextCachePtr) ctxt->cache;

	if ((cache->numberObjs != NULL) &&
	    (cache->numberObjs->number != 0))
	{
	    xmlXPathObjectPtr ret;

	    ret = (xmlXPathObjectPtr)
		cache->numberObjs->items[--cache->numberObjs->number];
	    ret->type = XPATH_NUMBER;
	    ret->floatval = val;
#ifdef XP_DEBUG_OBJ_USAGE
	    xmlXPathDebugObjUsageRequested(ctxt, XPATH_NUMBER);
#endif
	    return(ret);
	} else if ((cache->miscObjs != NULL) &&
	    (cache->miscObjs->number != 0))
	{
	    xmlXPathObjectPtr ret;

	    ret = (xmlXPathObjectPtr)
		cache->miscObjs->items[--cache->miscObjs->number];

	    ret->type = XPATH_NUMBER;
	    ret->floatval = val;
#ifdef XP_DEBUG_OBJ_USAGE
	    xmlXPathDebugObjUsageRequested(ctxt, XPATH_NUMBER);
#endif
	    return(ret);
	}
    }
    return(xmlXPathNewFloat(val));
}
