static void init_reap_node(int cpu)
{
	per_cpu(slab_reap_node, cpu) = next_node_in(cpu_to_mem(cpu),
						    node_online_map);
}
