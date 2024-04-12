static void sc_asn1_print_integer(const u8 * buf, size_t buflen)
{
	size_t a = 0;

	if (buflen > sizeof(a)) {
		printf("0x%s", sc_dump_hex(buf, buflen));
	} else {
		size_t i;
		for (i = 0; i < buflen; i++) {
			a <<= 8;
			a |= buf[i];
		}
		printf("%"SC_FORMAT_LEN_SIZE_T"u", a);
	}
}
