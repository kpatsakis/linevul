void sctp_v6_pf_init(void)
{
	/* Register the SCTP specific PF_INET6 functions. */
	sctp_register_pf(&sctp_pf_inet6, PF_INET6);

	/* Register the SCTP specific AF_INET6 functions. */
	sctp_register_af(&sctp_af_inet6);
}
