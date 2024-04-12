static void check_spinlock_acquired(struct kmem_cache *cachep)
{
#ifdef CONFIG_SMP
	check_irq_off();
	assert_spin_locked(&get_node(cachep, numa_mem_id())->list_lock);
#endif
}
