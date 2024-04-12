ftrace_ops_test(struct ftrace_ops *ops, unsigned long ip)
{
	struct ftrace_hash *filter_hash;
	struct ftrace_hash *notrace_hash;
	int ret;

	filter_hash = rcu_dereference_raw(ops->filter_hash);
	notrace_hash = rcu_dereference_raw(ops->notrace_hash);

	if ((ftrace_hash_empty(filter_hash) ||
	     ftrace_lookup_ip(filter_hash, ip)) &&
	    (ftrace_hash_empty(notrace_hash) ||
	     !ftrace_lookup_ip(notrace_hash, ip)))
		ret = 1;
	else
		ret = 0;

	return ret;
}
