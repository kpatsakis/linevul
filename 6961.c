static bool append_ptyname(char **pp, char *name)
{
	char *p;

	if (!*pp) {
		*pp = malloc(strlen(name) + strlen("container_ttys=") + 1);
		if (!*pp)
			return false;
		sprintf(*pp, "container_ttys=%s", name);
		return true;
	}
	p = realloc(*pp, strlen(*pp) + strlen(name) + 2);
	if (!p)
		return false;
	*pp = p;
	strcat(p, " ");
	strcat(p, name);
	return true;
}
