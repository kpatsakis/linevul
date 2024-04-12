parse_server_match_config(ServerOptions *options,
   struct connection_info *connectinfo)
{
	ServerOptions mo;

	initialize_server_options(&mo);
	parse_server_config(&mo, "reprocess config", &cfg, connectinfo);
	copy_set_server_options(options, &mo, 0);
}
