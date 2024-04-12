void fs_private_homedir(void) {
	char *homedir = cfg.homedir;
	char *private_homedir = cfg.home_private;
	assert(homedir);
	assert(private_homedir);
	
	int xflag = store_xauthority();
	int aflag = store_asoundrc();
	
	uid_t u = getuid();
	gid_t g = getgid();
	struct stat s;
	if (stat(homedir, &s) == -1) {
		fprintf(stderr, "Error: cannot find user home directory\n");
		exit(1);
	}
	

	if (arg_debug)
		printf("Mount-bind %s on top of %s\n", private_homedir, homedir);
	if (mount(private_homedir, homedir, NULL, MS_NOSUID | MS_NODEV | MS_BIND | MS_REC, NULL) < 0)
		errExit("mount bind");
	fs_logger3("mount-bind", private_homedir, cfg.homedir);
	fs_logger2("whitelist", cfg.homedir);

	if (u != 0) {
		if (arg_debug)
			printf("Mounting a new /root directory\n");
		if (mount("tmpfs", "/root", "tmpfs", MS_NOSUID | MS_NODEV | MS_NOEXEC | MS_STRICTATIME | MS_REC,  "mode=700,gid=0") < 0)
			errExit("mounting home directory");
		fs_logger("tmpfs /root");
	}
	else {
		if (arg_debug)
			printf("Mounting a new /home directory\n");
		if (mount("tmpfs", "/home", "tmpfs", MS_NOSUID | MS_NODEV | MS_NOEXEC | MS_STRICTATIME | MS_REC,  "mode=755,gid=0") < 0)
			errExit("mounting home directory");
		fs_logger("tmpfs /home");
	}
	

	skel(homedir, u, g);
	if (xflag)
		copy_xauthority();
	if (aflag)
		copy_asoundrc();
}
