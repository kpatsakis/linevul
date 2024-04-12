memParseTest(const char *filename, const char *result,
             const char *err ATTRIBUTE_UNUSED,
	     int options ATTRIBUTE_UNUSED) {
    xmlDocPtr doc;
    const char *base;
    int size, res;

    nb_tests++;
    /*
     * load and parse the memory
     */
    if (loadMem(filename, &base, &size) != 0) {
        fprintf(stderr, "Failed to load %s\n", filename);
	return(-1);
    }

    doc = xmlReadMemory(base, size, filename, NULL, 0);
    unloadMem(base);
    if (doc == NULL) {
        return(1);
    }
    xmlDocDumpMemory(doc, (xmlChar **) &base, &size);
    xmlFreeDoc(doc);
    res = compareFileMem(result, base, size);
    if ((base == NULL) || (res != 0)) {
	if (base != NULL)
	    xmlFree((char *)base);
        fprintf(stderr, "Result for %s failed in %s\n", filename, result);
	return(-1);
    }
    xmlFree((char *)base);
    return(0);
}
