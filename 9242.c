static int create_cgroup(struct cgroup_mount_point *mp, const char *path)
{
	return create_or_remove_cgroup(false, mp, path, false);
}
