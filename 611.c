make_NegHints(OM_uint32 *minor_status, gss_buffer_t *outbuf)
{
	OM_uint32 major_status;
	unsigned int tlen = 0;
	unsigned int hintNameSize = 0;
	unsigned char *ptr;
	unsigned char *t;
	const char *hintname = "not_defined_in_RFC4178@please_ignore";
	const size_t hintname_len = strlen(hintname);

	*outbuf = GSS_C_NO_BUFFER;
	major_status = GSS_S_FAILURE;

	/* Length of DER encoded GeneralString */
	tlen = 1 + gssint_der_length_size(hintname_len) + hintname_len;
	hintNameSize = tlen;

	/* Length of DER encoded hintName */
	tlen += 1 + gssint_der_length_size(hintNameSize);

	t = gssalloc_malloc(tlen);
	if (t == NULL) {
		*minor_status = ENOMEM;
		goto errout;
	}

	ptr = t;

	*ptr++ = CONTEXT | 0x00; /* hintName identifier */
	if (gssint_put_der_length(hintNameSize,
				  &ptr, tlen - (int)(ptr-t)))
		goto errout;

	*ptr++ = GENERAL_STRING;
	if (gssint_put_der_length(hintname_len, &ptr, tlen - (int)(ptr-t)))
		goto errout;

	memcpy(ptr, hintname, hintname_len);
	ptr += hintname_len;

	*outbuf = (gss_buffer_t)malloc(sizeof(gss_buffer_desc));
	if (*outbuf == NULL) {
		*minor_status = ENOMEM;
		goto errout;
	}
	(*outbuf)->value = (void *)t;
	(*outbuf)->length = ptr - t;

	t = NULL; /* don't free */

	*minor_status = 0;
	major_status = GSS_S_COMPLETE;

errout:
	if (t != NULL) {
		free(t);
	}

	return (major_status);
}
