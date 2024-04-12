void xt_proto_fini(struct net *net, u_int8_t af)
{
#ifdef CONFIG_PROC_FS
	char buf[XT_FUNCTION_MAXNAMELEN];

	strlcpy(buf, xt_prefix[af], sizeof(buf));
	strlcat(buf, FORMAT_TABLES, sizeof(buf));
	remove_proc_entry(buf, net->proc_net);

	strlcpy(buf, xt_prefix[af], sizeof(buf));
	strlcat(buf, FORMAT_TARGETS, sizeof(buf));
	remove_proc_entry(buf, net->proc_net);

	strlcpy(buf, xt_prefix[af], sizeof(buf));
	strlcat(buf, FORMAT_MATCHES, sizeof(buf));
	remove_proc_entry(buf, net->proc_net);
#endif /*CONFIG_PROC_FS*/
}
