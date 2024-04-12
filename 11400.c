static inline void cleanup_cgroups(char *path)
{
	int i;
	char **slist = subsystems;

	if (cgm_supports_multiple_controllers)
		slist = subsystems_inone;
	for (i = 0; slist[i]; i++)
		cgm_remove_cgroup(slist[i], path);
}
