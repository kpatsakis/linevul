user_unregister (User *user)
{
        g_signal_handlers_disconnect_by_func (G_OBJECT (user), G_CALLBACK (on_user_property_notify), NULL);

        g_dbus_interface_skeleton_unexport (G_DBUS_INTERFACE_SKELETON (user));

        if (user->extension_ids) {
                guint i;

                for (i = 0; i < user->n_extension_ids; i++) {
                        /* In theory, if an error happened during registration, we could have 0 here. */
                        if (user->extension_ids[i] == 0)
                                continue;

                        g_dbus_connection_unregister_object (user->system_bus_connection, user->extension_ids[i]);
                }

                g_clear_pointer (&user->extension_ids, g_free);
                user->n_extension_ids = 0;
        }
}
