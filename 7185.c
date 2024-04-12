xmlCanonicPath(const xmlChar *path)
{
/*
 * For Windows implementations, additional work needs to be done to
 * replace backslashes in pathnames with "forward slashes"
 */
#if defined(_WIN32) && !defined(__CYGWIN__)
 int len = 0;
 int i = 0;
    xmlChar *p = NULL;
#endif
    xmlURIPtr uri;
    xmlChar *ret;
 const xmlChar *absuri;

 if (path == NULL)
 return(NULL);

#if defined(_WIN32)
 /*
     * We must not change the backslashes to slashes if the the path
     * starts with \\?\
     * Those paths can be up to 32k characters long.
     * Was added specifically for OpenOffice, those paths can't be converted
     * to URIs anyway.
     */
 if ((path[0] == '\\') && (path[1] == '\\') && (path[2] == '?') &&
 (path[3] == '\\') )
 return xmlStrdup((const xmlChar *) path);
#endif

 /* sanitize filename starting with // so it can be used as URI */
 if ((path[0] == '/') && (path[1] == '/') && (path[2] != '/'))
        path++;

 if ((uri = xmlParseURI((const char *) path)) != NULL) {
	xmlFreeURI(uri);
 return xmlStrdup(path);
 }

 /* Check if this is an "absolute uri" */
    absuri = xmlStrstr(path, BAD_CAST "://");
 if (absuri != NULL) {
 int l, j;
 unsigned char c;
	xmlChar *escURI;

 /*
	 * this looks like an URI where some parts have not been
	 * escaped leading to a parsing problem.  Check that the first
	 * part matches a protocol.
	 */
	l = absuri - path;
 /* Bypass if first part (part before the '://') is > 20 chars */
 if ((l <= 0) || (l > 20))
 goto path_processing;
 /* Bypass if any non-alpha characters are present in first part */
 for (j = 0;j < l;j++) {
	    c = path[j];
 if (!(((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'))))
 goto path_processing;
 }

 /* Escape all except the characters specified in the supplied path */
        escURI = xmlURIEscapeStr(path, BAD_CAST ":/?_.#&;=");
 if (escURI != NULL) {
 /* Try parsing the escaped path */
	    uri = xmlParseURI((const char *) escURI);
 /* If successful, return the escaped string */
 if (uri != NULL) {
	        xmlFreeURI(uri);
 return escURI;
 }
 }
 }

path_processing:
/* For Windows implementations, replace backslashes with 'forward slashes' */
#if defined(_WIN32) && !defined(__CYGWIN__)
 /*
     * Create a URI structure
     */
    uri = xmlCreateURI();
 if (uri == NULL) { /* Guard against 'out of memory' */
 return(NULL);
 }

    len = xmlStrlen(path);
 if ((len > 2) && IS_WINDOWS_PATH(path)) {
 /* make the scheme 'file' */
	uri->scheme = xmlStrdup(BAD_CAST "file");
 /* allocate space for leading '/' + path + string terminator */
	uri->path = xmlMallocAtomic(len + 2);
 if (uri->path == NULL) {
	    xmlFreeURI(uri); /* Guard agains 'out of memory' */
 return(NULL);
 }
 /* Put in leading '/' plus path */
	uri->path[0] = '/';
	p = uri->path + 1;
	strncpy(p, path, len + 1);
 } else {
	uri->path = xmlStrdup(path);
 if (uri->path == NULL) {
	    xmlFreeURI(uri);
 return(NULL);
 }
	p = uri->path;
 }
 /* Now change all occurences of '\' to '/' */
 while (*p != '\0') {
 if (*p == '\\')
 *p = '/';
	p++;
 }

 if (uri->scheme == NULL) {
	ret = xmlStrdup((const xmlChar *) uri->path);
 } else {
	ret = xmlSaveUri(uri);
 }

    xmlFreeURI(uri);
#else
    ret = xmlStrdup((const xmlChar *) path);
#endif
 return(ret);
}
