static inline void dn_socket_format_entry(struct seq_file *seq, struct sock *sk)
{
	struct dn_scp *scp = DN_SK(sk);
	char buf1[DN_ASCBUF_LEN];
	char buf2[DN_ASCBUF_LEN];
	char local_object[DN_MAXOBJL+3];
	char remote_object[DN_MAXOBJL+3];

	dn_printable_object(&scp->addr, local_object);
	dn_printable_object(&scp->peer, remote_object);

	seq_printf(seq,
		   "%6s/%04X %04d:%04d %04d:%04d %01d %-16s "
		   "%6s/%04X %04d:%04d %04d:%04d %01d %-16s %4s %s\n",
		   dn_addr2asc(le16_to_cpu(dn_saddr2dn(&scp->addr)), buf1),
		   scp->addrloc,
		   scp->numdat,
		   scp->numoth,
		   scp->ackxmt_dat,
		   scp->ackxmt_oth,
		   scp->flowloc_sw,
		   local_object,
		   dn_addr2asc(le16_to_cpu(dn_saddr2dn(&scp->peer)), buf2),
		   scp->addrrem,
		   scp->numdat_rcv,
		   scp->numoth_rcv,
		   scp->ackrcv_dat,
		   scp->ackrcv_oth,
		   scp->flowrem_sw,
		   remote_object,
		   dn_state2asc(scp->state),
		   ((scp->accept_mode == ACC_IMMED) ? "IMMED" : "DEFER"));
}
