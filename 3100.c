dump_extra(Buffer *buf)
{
    printf("W3m-current-url: %s\n", parsedURL2Str(&buf->currentURL)->ptr);
    if (buf->baseURL)
	printf("W3m-base-url: %s\n", parsedURL2Str(buf->baseURL)->ptr);
#ifdef USE_M17N
    printf("W3m-document-charset: %s\n",
	   wc_ces_to_charset(buf->document_charset));
#endif
#ifdef USE_SSL
    if (buf->ssl_certificate) {
	Str tmp = Strnew();
	char *p;
	for (p = buf->ssl_certificate; *p; p++) {
	    Strcat_char(tmp, *p);
	    if (*p == '\n') {
		for (; *(p + 1) == '\n'; p++) ;
		if (*(p + 1))
		    Strcat_char(tmp, '\t');
	    }
	}
	if (Strlastchar(tmp) != '\n')
	    Strcat_char(tmp, '\n');
	printf("W3m-ssl-certificate: %s", tmp->ptr);
    }
#endif
}
