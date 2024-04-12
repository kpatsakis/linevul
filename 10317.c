namecmp(const void *key, const void *name)
{
	return strcmp((char *)key, *(char **)name);
}
