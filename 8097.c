struct cg_proto *tcp_proto_cgroup(struct mem_cgroup *memcg)
{
	if (!memcg || mem_cgroup_is_root(memcg))
		return NULL;

	return &memcg->tcp_mem.cg_proto;
}
