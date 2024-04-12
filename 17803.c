nautilus_directory_monitor_remove_internal (NautilusDirectory *directory,
                                            NautilusFile      *file,
                                            gconstpointer      client)
{
    g_assert (NAUTILUS_IS_DIRECTORY (directory));
    g_assert (file == NULL || NAUTILUS_IS_FILE (file));
    g_assert (client != NULL);

    remove_monitor (directory, file, client);

    if (directory->details->monitor != NULL
        && directory->details->monitor_list == NULL)
    {
        nautilus_monitor_cancel (directory->details->monitor);
        directory->details->monitor = NULL;
    }

    /* XXX - do we need to remove anything from the work queue? */

    nautilus_directory_async_state_changed (directory);
}
