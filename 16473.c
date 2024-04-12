static void fib_flush(struct net *net)
{
	int flushed = 0;
	unsigned int h;

	for (h = 0; h < FIB_TABLE_HASHSZ; h++) {
		struct hlist_head *head = &net->ipv4.fib_table_hash[h];
		struct hlist_node *tmp;
		struct fib_table *tb;

		hlist_for_each_entry_safe(tb, tmp, head, tb_hlist)
			flushed += fib_table_flush(tb);
	}

	if (flushed)
		rt_cache_flush(net);
}
