parse_post_op_attr(netdissect_options *ndo,
                   const uint32_t *dp, int verbose)
{
	ND_TCHECK(dp[0]);
	if (!EXTRACT_32BITS(&dp[0]))
		return (dp + 1);
	dp++;
	if (verbose) {
		return parsefattr(ndo, dp, verbose, 1);
	} else
		return (dp + (NFSX_V3FATTR / sizeof (uint32_t)));
trunc:
	return (NULL);
}
