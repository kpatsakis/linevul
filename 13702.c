static void sc_asn1_print_generalizedtime(const u8 * buf, size_t buflen)
{
	if (buflen < 8) {
		printf("Error in decoding.\n");
		return;
	}

	print_ascii(buf, 2);
	sc_asn1_print_utctime(buf + 2, buflen - 2);
}
