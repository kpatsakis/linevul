check_password(const char *method,
               const char *ha1,
               const char *uri,
               const char *nonce,
               const char *nc,
               const char *cnonce,
               const char *qop,
               const char *response)
{
	char ha2[32 + 1], expected_response[32 + 1];

	/* Some of the parameters may be NULL */
	if ((method == NULL) || (nonce == NULL) || (nc == NULL) || (cnonce == NULL)
	    || (qop == NULL) || (response == NULL)) {
		return 0;
	}

	/* NOTE(lsm): due to a bug in MSIE, we do not compare the URI */
	if (strlen(response) != 32) {
		return 0;
	}

	mg_md5(ha2, method, ":", uri, NULL);
	mg_md5(expected_response,
	       ha1,
	       ":",
	       nonce,
	       ":",
	       nc,
	       ":",
	       cnonce,
	       ":",
	       qop,
	       ":",
	       ha2,
	       NULL);

	return mg_strcasecmp(response, expected_response) == 0;
}
