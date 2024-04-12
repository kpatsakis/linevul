static struct sock *raw_get_first(struct seq_file *seq)
{
	struct sock *sk;
	struct raw_iter_state *state = raw_seq_private(seq);

	for (state->bucket = 0; state->bucket < RAW_HTABLE_SIZE;
			++state->bucket) {
		struct hlist_node *node;

		sk_for_each(sk, node, &state->h->ht[state->bucket])
			if (sock_net(sk) == seq_file_net(seq))
				goto found;
	}
	sk = NULL;
found:
	return sk;
}
