xmlXPathCurrentChar(xmlXPathParserContextPtr ctxt, int *len) {
    unsigned char c;
    unsigned int val;
    const xmlChar *cur;

    if (ctxt == NULL)
	return(0);
    cur = ctxt->cur;

    /*
     * We are supposed to handle UTF8, check it's valid
     * From rfc2044: encoding of the Unicode values on UTF-8:
     *
     * UCS-4 range (hex.)           UTF-8 octet sequence (binary)
     * 0000 0000-0000 007F   0xxxxxxx
     * 0000 0080-0000 07FF   110xxxxx 10xxxxxx
     * 0000 0800-0000 FFFF   1110xxxx 10xxxxxx 10xxxxxx
     *
     * Check for the 0x110000 limit too
     */
    c = *cur;
    if (c & 0x80) {
	if ((cur[1] & 0xc0) != 0x80)
	    goto encoding_error;
	if ((c & 0xe0) == 0xe0) {

	    if ((cur[2] & 0xc0) != 0x80)
		goto encoding_error;
	    if ((c & 0xf0) == 0xf0) {
		if (((c & 0xf8) != 0xf0) ||
		    ((cur[3] & 0xc0) != 0x80))
		    goto encoding_error;
		/* 4-byte code */
		*len = 4;
		val = (cur[0] & 0x7) << 18;
		val |= (cur[1] & 0x3f) << 12;
		val |= (cur[2] & 0x3f) << 6;
		val |= cur[3] & 0x3f;
	    } else {
	      /* 3-byte code */
		*len = 3;
		val = (cur[0] & 0xf) << 12;
		val |= (cur[1] & 0x3f) << 6;
		val |= cur[2] & 0x3f;
	    }
	} else {
	  /* 2-byte code */
	    *len = 2;
	    val = (cur[0] & 0x1f) << 6;
	    val |= cur[1] & 0x3f;
	}
	if (!IS_CHAR(val)) {
	    XP_ERROR0(XPATH_INVALID_CHAR_ERROR);
	}
	return(val);
    } else {
	/* 1-byte code */
	*len = 1;
	return((int) *cur);
    }
encoding_error:
    /*
     * If we detect an UTF8 error that probably means that the
     * input encoding didn't get properly advertised in the
     * declaration header. Report the error and switch the encoding
     * to ISO-Latin-1 (if you don't like this policy, just declare the
     * encoding !)
     */
    *len = 0;
    XP_ERROR0(XPATH_ENCODING_ERROR);
}
