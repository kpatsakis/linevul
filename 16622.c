static ssize_t o2nm_cluster_attr_write(const char *page, ssize_t count,
                                       unsigned int *val)
{
	unsigned long tmp;
	char *p = (char *)page;

	tmp = simple_strtoul(p, &p, 0);
	if (!p || (*p && (*p != '\n')))
		return -EINVAL;

	if (tmp == 0)
		return -EINVAL;
	if (tmp >= (u32)-1)
		return -ERANGE;

	*val = tmp;

	return count;
}
