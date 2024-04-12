int lxc_setup(struct lxc_handler *handler)
{
	const char *name = handler->name;
	struct lxc_conf *lxc_conf = handler->conf;
	const char *lxcpath = handler->lxcpath;

	if (do_rootfs_setup(lxc_conf, name, lxcpath) < 0) {
		ERROR("Error setting up rootfs mount after spawn");
		return -1;
	}

	if (lxc_conf->inherit_ns_fd[LXC_NS_UTS] == -1) {
		if (setup_utsname(lxc_conf->utsname)) {
			ERROR("failed to setup the utsname for '%s'", name);
			return -1;
		}
	}

	if (setup_network(&lxc_conf->network)) {
		ERROR("failed to setup the network for '%s'", name);
		return -1;
	}

	if (lxc_conf->autodev > 0) {
		if (mount_autodev(name, &lxc_conf->rootfs, lxcpath)) {
			ERROR("failed to mount /dev in the container");
			return -1;
		}
	}

	/* do automatic mounts (mainly /proc and /sys), but exclude
	 * those that need to wait until other stuff has finished
	 */
	if (lxc_mount_auto_mounts(lxc_conf, lxc_conf->auto_mounts & ~LXC_AUTO_CGROUP_MASK, handler) < 0) {
		ERROR("failed to setup the automatic mounts for '%s'", name);
		return -1;
	}

	if (setup_mount(&lxc_conf->rootfs, lxc_conf->fstab, name)) {
		ERROR("failed to setup the mounts for '%s'", name);
		return -1;
	}

	if (!lxc_list_empty(&lxc_conf->mount_list) && setup_mount_entries(&lxc_conf->rootfs, &lxc_conf->mount_list, name)) {
		ERROR("failed to setup the mount entries for '%s'", name);
		return -1;
	}

	/* Make sure any start hooks are in the container */
	if (!verify_start_hooks(lxc_conf))
		return -1;

	if (lxc_conf->is_execute)
		lxc_execute_bind_init(lxc_conf);

	/* now mount only cgroup, if wanted;
	 * before, /sys could not have been mounted
	 * (is either mounted automatically or via fstab entries)
	 */
	if (lxc_mount_auto_mounts(lxc_conf, lxc_conf->auto_mounts & LXC_AUTO_CGROUP_MASK, handler) < 0) {
		ERROR("failed to setup the automatic mounts for '%s'", name);
		return -1;
	}

	if (run_lxc_hooks(name, "mount", lxc_conf, lxcpath, NULL)) {
		ERROR("failed to run mount hooks for container '%s'.", name);
		return -1;
	}

	if (lxc_conf->autodev > 0) {
		if (run_lxc_hooks(name, "autodev", lxc_conf, lxcpath, NULL)) {
			ERROR("failed to run autodev hooks for container '%s'.", name);
			return -1;
		}
		if (fill_autodev(&lxc_conf->rootfs)) {
			ERROR("failed to populate /dev in the container");
			return -1;
		}
	}

	if (!lxc_conf->is_execute && setup_console(&lxc_conf->rootfs, &lxc_conf->console, lxc_conf->ttydir)) {
		ERROR("failed to setup the console for '%s'", name);
		return -1;
	}

	if (lxc_conf->kmsg) {
		if (setup_kmsg(&lxc_conf->rootfs, &lxc_conf->console))  // don't fail
			ERROR("failed to setup kmsg for '%s'", name);
	}

	if (!lxc_conf->is_execute && setup_dev_symlinks(&lxc_conf->rootfs)) {
		ERROR("failed to setup /dev symlinks for '%s'", name);
		return -1;
	}

	/* mount /proc if it's not already there */
	if (tmp_proc_mount(lxc_conf) < 0) {
		ERROR("failed to LSM mount proc for '%s'", name);
		return -1;
	}

	if (setup_pivot_root(&lxc_conf->rootfs)) {
		ERROR("failed to set rootfs for '%s'", name);
		return -1;
	}

	if (setup_pts(lxc_conf->pts)) {
		ERROR("failed to setup the new pts instance");
		return -1;
	}

	if (lxc_create_tty(name, lxc_conf)) {
		ERROR("failed to create the ttys");
		return -1;
	}

	if (send_ttys_to_parent(handler) < 0) {
		ERROR("failure sending console info to parent");
		return -1;
	}


	if (!lxc_conf->is_execute && setup_tty(lxc_conf)) {
		ERROR("failed to setup the ttys for '%s'", name);
		return -1;
	}

	if (lxc_conf->pty_names && setenv("container_ttys", lxc_conf->pty_names, 1))
		SYSERROR("failed to set environment variable for container ptys");


	if (setup_personality(lxc_conf->personality)) {
		ERROR("failed to setup personality");
		return -1;
	}

	if (!lxc_list_empty(&lxc_conf->keepcaps)) {
		if (!lxc_list_empty(&lxc_conf->caps)) {
			ERROR("Simultaneously requested dropping and keeping caps");
			return -1;
		}
		if (dropcaps_except(&lxc_conf->keepcaps)) {
			ERROR("failed to keep requested caps");
			return -1;
		}
	} else if (setup_caps(&lxc_conf->caps)) {
		ERROR("failed to drop capabilities");
		return -1;
	}

	NOTICE("'%s' is setup.", name);

	return 0;
}
