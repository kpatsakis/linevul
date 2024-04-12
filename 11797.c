static void sctp_do_ecn_ce_work(struct sctp_association *asoc,
				__u32 lowest_tsn)
{
	/* Save the TSN away for comparison when we receive CWR */

	asoc->last_ecne_tsn = lowest_tsn;
	asoc->need_ecne = 1;
}
