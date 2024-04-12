static ssize_t o2nm_node_ipv4_port_store(struct config_item *item,
					 const char *page, size_t count)
{
	struct o2nm_node *node = to_o2nm_node(item);
	unsigned long tmp;
	char *p = (char *)page;

	tmp = simple_strtoul(p, &p, 0);
	if (!p || (*p && (*p != '\n')))
		return -EINVAL;

	if (tmp == 0)
		return -EINVAL;
	if (tmp >= (u16)-1)
		return -ERANGE;

	if (test_and_set_bit(O2NM_NODE_ATTR_PORT, &node->nd_set_attributes))
		return -EBUSY;
	node->nd_ipv4_port = htons(tmp);

	return count;
}
