char *M_fs_path_user_confdir(M_fs_system_t sys_type)
{
	char         *out;
	M_fs_error_t  res;

#ifdef _WIN32
	res = M_fs_path_norm(&out, "%APPDATA%", M_FS_PATH_NORM_NONE, sys_type);
#elif defined(__APPLE__)
	res = M_fs_path_norm(&out, "~/Library/Application Support/", M_FS_PATH_NORM_HOME, sys_type);
#else
	res = M_fs_path_norm(&out, "~/.config", M_FS_PATH_NORM_HOME, sys_type);
#endif
	if (res != M_FS_ERROR_SUCCESS)
		return NULL;
	return out;
}
