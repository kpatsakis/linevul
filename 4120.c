static void pppol2tp_next_session(struct net *net, struct pppol2tp_seq_data *pd)
{
	pd->session = l2tp_session_find_nth(pd->tunnel, pd->session_idx);
	pd->session_idx++;

	if (pd->session == NULL) {
		pd->session_idx = 0;
		pppol2tp_next_tunnel(net, pd);
	}
}
