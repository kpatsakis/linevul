int lxc_clear_automounts(struct lxc_conf *c)
{
	c->auto_mounts = 0;
	return 0;
}
