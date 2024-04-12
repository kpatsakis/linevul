bool ikev1_ship_chain(chunk_t *chain, int n, pb_stream *outs,
					     u_int8_t type,
					     u_int8_t setnp)
{
	int i;
	u_int8_t np;

	for (i = 0; i < n; i++) {
		/* set np for last cert, or another */
		np = i == n - 1 ? setnp : ISAKMP_NEXT_CERT;

		if (!ikev1_ship_CERT(type, chain[i], outs, np))
			return FALSE;
	}

	return TRUE;
}
