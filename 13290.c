sc_asn1_decode_object_id(const u8 *inbuf, size_t inlen, struct sc_object_id *id)
{
	int a;
	const u8 *p = inbuf;
	int *octet;

	if (inlen == 0 || inbuf == NULL || id == NULL)
		return SC_ERROR_INVALID_ARGUMENTS;

	sc_init_oid(id);
	octet = id->value;

	a = *p;
	*octet++ = a / 40;
	*octet++ = a % 40;
	inlen--;

	while (inlen) {
		p++;
		a = *p & 0x7F;
		inlen--;
		while (inlen && *p & 0x80) {
			p++;
			a <<= 7;
			a |= *p & 0x7F;
			inlen--;
		}
		*octet++ = a;
		if (octet - id->value >= SC_MAX_OBJECT_ID_OCTETS)   {
			sc_init_oid(id);
			return SC_ERROR_INVALID_ASN1_OBJECT;
		}
	};

	return 0;
}
