static struct sock *__l2cap_get_chan_by_scid(struct l2cap_chan_list *l, u16 cid)
{
	struct sock *s;
	for (s = l->head; s; s = l2cap_pi(s)->next_c) {
		if (l2cap_pi(s)->scid == cid)
			break;
	}
	return s;
}
