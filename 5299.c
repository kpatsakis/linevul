static ZEND_RESULT_CODE parse_idn(struct parse_state *state, size_t prev_len)
{
	char *idn = NULL;
	int rv = -1;
	TSRMLS_FETCH_FROM_CTX(state->ts);

	if (state->flags & PHP_HTTP_URL_PARSE_MBUTF8) {
		rv = idna_to_ascii_8z(state->url.host, &idn, IDNA_ALLOW_UNASSIGNED|IDNA_USE_STD3_ASCII_RULES);
	}
#	ifdef PHP_HTTP_HAVE_WCHAR
	else if (state->flags & PHP_HTTP_URL_PARSE_MBLOC) {
		rv = idna_to_ascii_lz(state->url.host, &idn, IDNA_ALLOW_UNASSIGNED|IDNA_USE_STD3_ASCII_RULES);
	}
#	endif
	if (rv != IDNA_SUCCESS) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Failed to parse IDN; %s", idna_strerror(rv));
		return FAILURE;
	} else {
		size_t idnlen = strlen(idn);
		memcpy(state->url.host, idn, idnlen + 1);
		free(idn);
		state->offset += idnlen - prev_len;
		return SUCCESS;
	}
}
