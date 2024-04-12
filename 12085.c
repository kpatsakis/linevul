static int dev_get_valid_name(struct net *net, const char *name, char *buf,
			      bool fmt)
{
	if (!dev_valid_name(name))
		return -EINVAL;

	if (fmt && strchr(name, '%'))
		return __dev_alloc_name(net, name, buf);
	else if (__dev_get_by_name(net, name))
		return -EEXIST;
	else if (buf != name)
		strlcpy(buf, name, IFNAMSIZ);

	return 0;
}
