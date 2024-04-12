static char *lxc_cgroup_get_hierarchy_abs_path(const char *subsystem, const char *name, const char *lxcpath)
{
	struct cgroup_meta_data *meta;
	struct cgroup_process_info *base_info, *info;
	struct cgroup_mount_point *mp;
	char *result = NULL;

	meta = lxc_cgroup_load_meta();
	if (!meta)
		return NULL;
	base_info = lxc_cgroup_get_container_info(name, lxcpath, meta);
	if (!base_info)
		goto out1;
	info = find_info_for_subsystem(base_info, subsystem);
	if (!info)
		goto out2;
	if (info->designated_mount_point) {
		mp = info->designated_mount_point;
	} else {
		mp = lxc_cgroup_find_mount_point(info->hierarchy, info->cgroup_path, true);
		if (!mp)
			goto out3;
	}
	result = cgroup_to_absolute_path(mp, info->cgroup_path, NULL);
out3:
out2:
	lxc_cgroup_process_info_free(base_info);
out1:
	lxc_cgroup_put_meta(meta);
	return result;
}
