create_sim_node(
	attr_val_fifo *		init_opts,
	server_info_fifo *	servers
	)
{
	sim_node *my_node;
	
	my_node = emalloc(sizeof(*my_node));
	my_node->init_opts = init_opts;
	my_node->servers = servers;

	return my_node;
}
