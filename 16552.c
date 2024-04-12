load_all_cursors_from_dir(const char *path, int size,
			  void (*load_callback)(XcursorImages *, void *),
			  void *user_data)
{
	FILE *f;
	DIR *dir = opendir(path);
	struct dirent *ent;
	char *full;
	XcursorImages *images;

	if (!dir)
		return;

	for(ent = readdir(dir); ent; ent = readdir(dir)) {
#ifdef _DIRENT_HAVE_D_TYPE
		if (ent->d_type != DT_UNKNOWN &&
		    (ent->d_type != DT_REG && ent->d_type != DT_LNK))
			continue;
#endif

		full = _XcursorBuildFullname(path, "", ent->d_name);
		if (!full)
			continue;

		f = fopen(full, "r");
		if (!f) {
			free(full);
			continue;
		}

		images = XcursorFileLoadImages(f, size);

		if (images) {
			XcursorImagesSetName(images, ent->d_name);
			load_callback(images, user_data);
		}

		fclose (f);
		free(full);
	}

	closedir(dir);
}
