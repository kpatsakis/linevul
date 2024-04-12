wb_drawop(netdissect_options *ndo,
          const struct pkt_dop *dop, u_int len)
{
	ND_PRINT((ndo, " wb-dop:"));
	if (len < sizeof(*dop) || !ND_TTEST(*dop))
		return (-1);
	len -= sizeof(*dop);

	ND_PRINT((ndo, " %s:%u<%u:%u>",
	    ipaddr_string(ndo, &dop->pd_page.p_sid),
	    EXTRACT_32BITS(&dop->pd_page.p_uid),
	    EXTRACT_32BITS(&dop->pd_sseq),
	    EXTRACT_32BITS(&dop->pd_eseq)));

	if (ndo->ndo_vflag)
		return (wb_dops(ndo, dop,
				EXTRACT_32BITS(&dop->pd_sseq),
				EXTRACT_32BITS(&dop->pd_eseq)));
	return (0);
}
