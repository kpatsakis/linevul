void preproc_build_firejail_dir(void) {
	struct stat s;

	if (stat(RUN_FIREJAIL_BASEDIR, &s)) {
		create_empty_dir_as_root(RUN_FIREJAIL_BASEDIR, 0755);
	}

	if (stat(RUN_FIREJAIL_DIR, &s)) {
		create_empty_dir_as_root(RUN_FIREJAIL_DIR, 0755);
	}

	if (stat(RUN_FIREJAIL_NETWORK_DIR, &s)) {
		create_empty_dir_as_root(RUN_FIREJAIL_NETWORK_DIR, 0755);
	}

	if (stat(RUN_FIREJAIL_BANDWIDTH_DIR, &s)) {
		create_empty_dir_as_root(RUN_FIREJAIL_BANDWIDTH_DIR, 0755);
	}

	if (stat(RUN_FIREJAIL_NAME_DIR, &s)) {
		create_empty_dir_as_root(RUN_FIREJAIL_NAME_DIR, 0755);
	}

	if (stat(RUN_FIREJAIL_PROFILE_DIR, &s)) {
		create_empty_dir_as_root(RUN_FIREJAIL_PROFILE_DIR, 0755);
	}

	if (stat(RUN_FIREJAIL_X11_DIR, &s)) {
		create_empty_dir_as_root(RUN_FIREJAIL_X11_DIR, 0755);
	}

	if (stat(RUN_FIREJAIL_APPIMAGE_DIR, &s)) {
		create_empty_dir_as_root(RUN_FIREJAIL_APPIMAGE_DIR, 0755);
	}

	if (stat(RUN_FIREJAIL_LIB_DIR, &s)) {
		create_empty_dir_as_root(RUN_FIREJAIL_LIB_DIR, 0755);
	}

	if (stat(RUN_MNT_DIR, &s)) {
		create_empty_dir_as_root(RUN_MNT_DIR, 0755);
	}

	create_empty_file_as_root(RUN_RO_FILE, S_IRUSR);
	create_empty_dir_as_root(RUN_RO_DIR, S_IRUSR);
}
