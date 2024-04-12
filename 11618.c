static void mem_cgroup_cancel_attach(struct cgroup_subsys *ss,
				struct cgroup *cgroup,
				struct cgroup_taskset *tset)
{
	mem_cgroup_clear_mc();
}
