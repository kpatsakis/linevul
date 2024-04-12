static struct fwnet_partial_datagram *fwnet_pd_find(struct fwnet_peer *peer,
						    u16 datagram_label)
{
	struct fwnet_partial_datagram *pd;

	list_for_each_entry(pd, &peer->pd_list, pd_link)
		if (pd->datagram_label == datagram_label)
			return pd;

	return NULL;
}
