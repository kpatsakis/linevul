static int s_write(Ssh ssh, void *data, int len)
{
    if (ssh->logctx)
	log_packet(ssh->logctx, PKT_OUTGOING, -1, NULL, data, len,
		   0, NULL, NULL, 0, NULL);
    if (!ssh->s)
        return 0;
    return sk_write(ssh->s, (char *)data, len);
}
