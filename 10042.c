print_32bits_val(netdissect_options *ndo, const uint32_t *dat)
{
	ND_PRINT((ndo, "%lu", (u_long)EXTRACT_32BITS(dat)));
}
