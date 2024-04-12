compare_forward(struct Forward *a, struct Forward *b)
{
	if (!compare_host(a->listen_host, b->listen_host))
		return 0;
	if (!compare_host(a->listen_path, b->listen_path))
		return 0;
	if (a->listen_port != b->listen_port)
		return 0;
	if (!compare_host(a->connect_host, b->connect_host))
		return 0;
	if (!compare_host(a->connect_path, b->connect_path))
		return 0;
	if (a->connect_port != b->connect_port)
		return 0;

	return 1;
}
