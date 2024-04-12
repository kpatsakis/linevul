char *lxc_append_paths(const char *first, const char *second)
{
	size_t len = strlen(first) + strlen(second) + 1;
	const char *pattern = "%s%s";
	char *result = NULL;

	if (second[0] != '/') {
		len += 1;
		pattern = "%s/%s";
	}

	result = calloc(1, len);
	if (!result)
		return NULL;

	snprintf(result, len, pattern, first, second);
	return result;
}
