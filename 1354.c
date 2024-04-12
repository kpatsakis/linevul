tilde_expand_paths(char **paths, u_int num_paths)
{
	u_int i;
	char *cp;

	for (i = 0; i < num_paths; i++) {
		cp = tilde_expand_filename(paths[i], original_real_uid);
		free(paths[i]);
		paths[i] = cp;
	}
}
