int do_rootfs_setup(struct lxc_conf *conf, const char *name, const char *lxcpath)
{
	if (conf->rootfs_setup) {
		/*
		 * rootfs was set up in another namespace.  bind-mount it
		 * to give us a mount in our own ns so we can pivot_root to it
		 */
		const char *path = conf->rootfs.mount;
		if (mount(path, path, "rootfs", MS_BIND, NULL) < 0) {
			ERROR("Failed to bind-mount container / onto itself");
			return -1;
		}
		return 0;
	}

	remount_all_slave();

	if (run_lxc_hooks(name, "pre-mount", conf, lxcpath, NULL)) {
		ERROR("failed to run pre-mount hooks for container '%s'.", name);
		return -1;
	}

	if (setup_rootfs(conf)) {
		ERROR("failed to setup rootfs for '%s'", name);
		return -1;
	}

	conf->rootfs_setup = true;
	return 0;
}
