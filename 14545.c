ikev2_eap_print(netdissect_options *ndo, u_char tpay,
		const struct isakmp_gen *ext,
		u_int item_len _U_, const u_char *ep _U_,
		uint32_t phase _U_, uint32_t doi _U_,
		uint32_t proto _U_, int depth _U_)
{
	return ikev2_gen_print(ndo, tpay, ext);
}
