static int mem_control_numa_stat_open(struct inode *unused, struct file *file)
{
	struct cgroup *cont = file->f_dentry->d_parent->d_fsdata;

	file->f_op = &mem_control_numa_stat_file_operations;
	return single_open(file, mem_control_numa_stat_show, cont);
}
