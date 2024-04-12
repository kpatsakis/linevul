valid_path_cmp(const char *path, const char *valid_path)
{
	for ( ; *path && *valid_path; path++, valid_path++) {
		if (!isalnum(*path)) {
			if (*valid_path != '_')
				return true;
		}
		else if (*path != *valid_path)
			return true;
	}

	return *path != *valid_path;
}
