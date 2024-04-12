cleanup_socket(void)
{
	if (cleanup_pid != 0 && getpid() != cleanup_pid)
		return;
	debug("%s: cleanup", __func__);
	if (socket_name[0])
		unlink(socket_name);
	if (socket_dir[0])
		rmdir(socket_dir);
}
