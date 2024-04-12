uriPathTest(const char *filename ATTRIBUTE_UNUSED,
             const char *result ATTRIBUTE_UNUSED,
             const char *err ATTRIBUTE_UNUSED,
             int options ATTRIBUTE_UNUSED) {
    int parsed;
    int failures = 0;

    /*
     * register the new I/O handlers
     */
    if (xmlRegisterInputCallbacks(uripMatch, uripOpen, uripRead, uripClose) < 0)
    {
        fprintf(stderr, "failed to register HTTP handler\n");
	return(-1);
    }

    for (urip_current = 0;urip_testURLs[urip_current] != NULL;urip_current++) {
        urip_success = 1;
        parsed = urip_checkURL(urip_testURLs[urip_current]);
	if (urip_success != 1) {
	    fprintf(stderr, "failed the URL passing test for %s",
	            urip_testURLs[urip_current]);
	    failures++;
	} else if (parsed != 1) {
	    fprintf(stderr, "failed the parsing test for %s",
	            urip_testURLs[urip_current]);
	    failures++;
	}
	nb_tests++;
    }

    xmlPopInputCallbacks();
    return(failures);
}
