static void migrate_to_reboot_cpu(void)
{
 /* The boot cpu is always logical cpu 0 */
 int cpu = 0;

	cpu_hotplug_disable();

 /* Make certain the cpu I'm about to reboot on is online */
 if (!cpu_online(cpu))
		cpu = cpumask_first(cpu_online_mask);

 /* Prevent races with other tasks migrating this task */
	current->flags |= PF_NO_SETAFFINITY;

 /* Make certain I only run on the appropriate processor */
	set_cpus_allowed_ptr(current, cpumask_of(cpu));
}
