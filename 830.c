static void free_types_list(char *list[])
{
	char **n;

	if (!list)
		return;
	for (n = list; *n; n++)
		free(*n);
	free(list);
}
