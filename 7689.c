dbus_remove_object(vrrp_t *vrrp)
{
	dbus_unregister_object(vrrp->iname);
}
