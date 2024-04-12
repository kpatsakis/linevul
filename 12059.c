static struct cgroup_meta_data *lxc_cgroup_put_meta(struct cgroup_meta_data *meta_data)
{
	size_t i;
	if (!meta_data)
		return NULL;
	if (--meta_data->ref > 0)
		return meta_data;
	lxc_free_array((void **)meta_data->mount_points, (lxc_free_fn)lxc_cgroup_mount_point_free);
	if (meta_data->hierarchies) {
		for (i = 0; i <= meta_data->maximum_hierarchy; i++)
			lxc_cgroup_hierarchy_free(meta_data->hierarchies[i]);
	}
	free(meta_data->hierarchies);
	free(meta_data);
	return NULL;
}
