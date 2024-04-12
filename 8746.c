void sctp_v6_del_protocol(void)
{
	inet6_del_protocol(&sctpv6_protocol, IPPROTO_SCTP);
	unregister_inet6addr_notifier(&sctp_inet6addr_notifier);
}
