void ping_seq_stop(struct seq_file *seq, void *v)
{
	read_unlock_bh(&ping_table.lock);
}
