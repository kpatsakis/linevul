xmlParse3986RelativeRef(xmlURIPtr uri, const char *str) {
 int ret;

 if ((*str == '/') && (*(str + 1) == '/')) {
        str += 2;
	ret = xmlParse3986Authority(uri, &str);
 if (ret != 0) return(ret);
	ret = xmlParse3986PathAbEmpty(uri, &str);
 if (ret != 0) return(ret);
 } else if (*str == '/') {
	ret = xmlParse3986PathAbsolute(uri, &str);
 if (ret != 0) return(ret);
 } else if (ISA_PCHAR(str)) {
        ret = xmlParse3986PathNoScheme(uri, &str);
 if (ret != 0) return(ret);
 } else {
 /* path-empty is effectively empty */
 if (uri != NULL) {
 if (uri->path != NULL) xmlFree(uri->path);
	    uri->path = NULL;
 }
 }

 if (*str == '?') {
	str++;
	ret = xmlParse3986Query(uri, &str);
 if (ret != 0) return(ret);
 }
 if (*str == '#') {
	str++;
	ret = xmlParse3986Fragment(uri, &str);
 if (ret != 0) return(ret);
 }
 if (*str != 0) {
	xmlCleanURI(uri);
 return(1);
 }
 return(0);
}
