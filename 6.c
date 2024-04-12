exsltCryptoMd5Function (xmlXPathParserContextPtr ctxt, int nargs) {

    int str_len = 0;
    xmlChar *str = NULL, *ret = NULL;
    unsigned char hash[HASH_DIGEST_LENGTH];
    unsigned char hex[MD5_DIGEST_LENGTH * 2 + 1];

    str_len = exsltCryptoPopString (ctxt, nargs, &str);
    if (str_len == 0) {
	xmlXPathReturnEmptyString (ctxt);
	xmlFree (str);
	return;
    }

    PLATFORM_HASH (ctxt, PLATFORM_MD5, (const char *) str, str_len,
		   (char *) hash);
    exsltCryptoBin2Hex (hash, sizeof (hash) - 1, hex, sizeof (hex) - 1);

    ret = xmlStrdup ((xmlChar *) hex);
    xmlXPathReturnString (ctxt, ret);

    if (str != NULL)
	xmlFree (str);
}
