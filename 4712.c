dbus_object_create_path_vrrp(void)
{
	return g_strconcat(DBUS_VRRP_OBJECT_ROOT,
#if HAVE_DECL_CLONE_NEWNET
			  global_data->network_namespace ? "/" : "", global_data->network_namespace ? global_data->network_namespace : "",
#endif
			  global_data->instance_name ? "/" : "", global_data->instance_name ? global_data->instance_name : "",

			  "/Vrrp", NULL);
}
