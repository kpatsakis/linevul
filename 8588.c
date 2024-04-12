static void *dn_socket_seq_next(struct seq_file *seq, void *v, loff_t *pos)
{
	void *rc;

	if (v == SEQ_START_TOKEN) {
		rc = dn_socket_get_idx(seq, 0);
		goto out;
	}

	rc = dn_socket_get_next(seq, v);
	if (rc)
		goto out;
	read_unlock_bh(&dn_hash_lock);
out:
	++*pos;
	return rc;
}
