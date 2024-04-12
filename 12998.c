int open_related_ns(struct ns_common *ns,
		   struct ns_common *(*get_ns)(struct ns_common *ns))
{
	struct path path = {};
	struct file *f;
	void *err;
	int fd;

	fd = get_unused_fd_flags(O_CLOEXEC);
	if (fd < 0)
		return fd;

	while (1) {
		struct ns_common *relative;

		relative = get_ns(ns);
		if (IS_ERR(relative)) {
			put_unused_fd(fd);
			return PTR_ERR(relative);
		}

		err = __ns_get_path(&path, relative);
		if (IS_ERR(err) && PTR_ERR(err) == -EAGAIN)
			continue;
		break;
	}
	if (IS_ERR(err)) {
		put_unused_fd(fd);
		return PTR_ERR(err);
	}

	f = dentry_open(&path, O_RDONLY, current_cred());
	path_put(&path);
	if (IS_ERR(f)) {
		put_unused_fd(fd);
		fd = PTR_ERR(f);
	} else
		fd_install(fd, f);

	return fd;
}
