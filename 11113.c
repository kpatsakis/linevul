static void sctp_v6_seq_dump_addr(struct seq_file *seq, union sctp_addr *addr)
{
	seq_printf(seq, "%pI6 ", &addr->v6.sin6_addr);
}
