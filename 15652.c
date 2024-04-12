int lxc_clear_config_network(struct lxc_conf *c)
{
	struct lxc_list *it,*next;
	lxc_list_for_each_safe(it, &c->network, next) {
		lxc_remove_nic(it);
	}
	return 0;
}
