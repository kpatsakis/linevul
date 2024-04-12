static int proc_cwd_link(struct inode *inode, struct path *path)
{
	struct task_struct *task = get_proc_task(inode);
	int result = -ENOENT;

	if (task) {
		result = get_fs_path(task, path, 0);
		put_task_struct(task);
	}
	return result;
}
