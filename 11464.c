struct pathnames *add_subdir(struct pathnames *paths, struct pathname *path)
{
	if(paths->count % PATHS_ALLOC_SIZE == 0) {
		paths = realloc(paths, sizeof(struct pathnames *) +
			(paths->count + PATHS_ALLOC_SIZE) *
			sizeof(struct pathname *));
		if(paths == NULL)
			EXIT_UNSQUASH("Out of memory in add_subdir\n");
	}

	paths->path[paths->count++] = path;
	return paths;
}
