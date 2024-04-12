get_interface_ids(const gchar *object_path, gchar *interface, uint8_t *vrid, uint8_t *family)
{
	int path_length = DBUS_VRRP_INSTANCE_PATH_DEFAULT_LENGTH;
	gchar **dirs;
	char *endptr;

#if HAVE_DECL_CLONE_NEWNET
	if(global_data->network_namespace)
		path_length++;
#endif
	if(global_data->instance_name)
		path_length++;

	/* object_path will have interface, vrid and family as
	 * the third to last, second to last and last levels */
	dirs = g_strsplit(object_path, "/", path_length);
	strcpy(interface, dirs[path_length-3]);
	*vrid = (uint8_t)strtoul(dirs[path_length-2], &endptr, 10);
	if (*endptr)
		log_message(LOG_INFO, "Dbus unexpected characters '%s' at end of number '%s'", endptr, dirs[path_length-2]);
	*family = !g_strcmp0(dirs[path_length-1], "IPv4") ? AF_INET : !g_strcmp0(dirs[path_length-1], "IPv6") ? AF_INET6 : AF_UNSPEC;

	/* We are finished with all the object_path strings now */
	g_strfreev(dirs);
}
