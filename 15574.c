static inline void rt_free(struct rtable *rt)
{
	call_rcu(&rt->dst.rcu_head, dst_rcu_free);
}
