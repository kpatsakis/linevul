static void sctp_v4_get_saddr(struct sctp_sock *sk,
			      struct sctp_transport *t,
			      struct flowi *fl)
{
	union sctp_addr *saddr = &t->saddr;
	struct rtable *rt = (struct rtable *)t->dst;

	if (rt) {
		saddr->v4.sin_family = AF_INET;
		saddr->v4.sin_addr.s_addr = fl->u.ip4.saddr;
	}
}
