activate_parameters_install_free (ActivateParametersInstall *parameters_install)
{
    if (parameters_install->slot)
    {
        g_object_remove_weak_pointer (G_OBJECT (parameters_install->slot), (gpointer *) &parameters_install->slot);
    }
    if (parameters_install->parent_window)
    {
        g_object_remove_weak_pointer (G_OBJECT (parameters_install->parent_window), (gpointer *) &parameters_install->parent_window);
    }

    if (parameters_install->proxy != NULL)
    {
        g_object_unref (parameters_install->proxy);
    }

    nautilus_file_unref (parameters_install->file);
    nautilus_file_list_free (parameters_install->files);
    g_free (parameters_install->activation_directory);
    g_free (parameters_install->uri);
    g_free (parameters_install);
}
