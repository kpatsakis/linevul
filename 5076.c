static int register_memsw_files(struct cgroup *cont, struct cgroup_subsys *ss)
{
	if (!do_swap_account)
		return 0;
	return cgroup_add_files(cont, ss, memsw_cgroup_files,
				ARRAY_SIZE(memsw_cgroup_files));
};
