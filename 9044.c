void hostap_set_multicast_list_queue(struct work_struct *work)
{
	local_info_t *local =
		container_of(work, local_info_t, set_multicast_list_queue);
	struct net_device *dev = local->dev;

	if (hostap_set_word(dev, HFA384X_RID_PROMISCUOUSMODE,
			    local->is_promisc)) {
		printk(KERN_INFO "%s: %sabling promiscuous mode failed\n",
		       dev->name, local->is_promisc ? "en" : "dis");
	}
}
