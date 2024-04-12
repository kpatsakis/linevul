xmlPointerListCreate(int initialSize)
{
    xmlPointerListPtr ret;

    ret = xmlMalloc(sizeof(xmlPointerList));
    if (ret == NULL) {
	xmlXPathErrMemory(NULL,
	    "xmlPointerListCreate: allocating item\n");
	return (NULL);
    }
    memset(ret, 0, sizeof(xmlPointerList));
    if (initialSize > 0) {
	xmlPointerListAddSize(ret, NULL, initialSize);
	ret->number = 0;
    }
    return (ret);
}
