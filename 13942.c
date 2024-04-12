static struct sock *netlink_seq_socket_idx(struct seq_file *seq, loff_t pos)
{
	struct nl_seq_iter *iter = seq->private;
	int i, j;
	struct sock *s;
	struct hlist_node *node;
	loff_t off = 0;

	for (i = 0; i < MAX_LINKS; i++) {
		struct nl_pid_hash *hash = &nl_table[i].hash;

		for (j = 0; j <= hash->mask; j++) {
			sk_for_each(s, node, &hash->table[j]) {
				if (sock_net(s) != seq_file_net(seq))
					continue;
				if (off == pos) {
					iter->link = i;
					iter->hash_idx = j;
					return s;
				}
				++off;
			}
		}
	}
	return NULL;
}
