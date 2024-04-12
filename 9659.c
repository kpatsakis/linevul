xmlParse3986PathAbEmpty(xmlURIPtr uri, const char **str)
{
 const char *cur;
 int ret;

    cur = *str;

 while (*cur == '/') {
        cur++;
	ret = xmlParse3986Segment(&cur, 0, 1);
 if (ret != 0) return(ret);
 }
 if (uri != NULL) {
 if (uri->path != NULL) xmlFree(uri->path);
 if (*str != cur) {
 if (uri->cleanup & 2)
                uri->path = STRNDUP(*str, cur - *str);
 else
                uri->path = xmlURIUnescapeString(*str, cur - *str, NULL);
 } else {
            uri->path = NULL;
 }
 }
 *str = cur;
 return (0);
}
