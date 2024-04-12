char *M_fs_path_join_resolved(const char *path, const char *part, const char *resolved_name, M_fs_system_t sys_type)
{
	char *full_path;
	char *dir;
	char *rpath;

	if ((path == NULL || *path == '\0') && (part == NULL || *part == '\0') && (resolved_name == NULL || *resolved_name == '\0'))
		return NULL;

	sys_type = M_fs_path_get_system_type(sys_type);

	/* If the resolved path is absolute we don't need to modify it. */
	if (M_fs_path_isabs(resolved_name, sys_type))
		return M_strdup(resolved_name);

	full_path = M_fs_path_join(path, part, sys_type);
	M_fs_path_split(full_path, &dir, NULL, sys_type);
	M_free(full_path);

	rpath = M_fs_path_join(dir, resolved_name, sys_type);
	M_free(dir);

	return rpath;
}
