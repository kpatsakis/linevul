static int compat_update_counters(struct net *net, void __user *user,
				  unsigned int len)
{
	struct compat_ebt_replace hlp;

	if (copy_from_user(&hlp, user, sizeof(hlp)))
		return -EFAULT;

	/* try real handler in case userland supplied needed padding */
	if (len != sizeof(hlp) + hlp.num_counters * sizeof(struct ebt_counter))
		return update_counters(net, user, len);

	return do_update_counters(net, hlp.name, compat_ptr(hlp.counters),
					hlp.num_counters, user, len);
}
