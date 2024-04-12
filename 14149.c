nautilus_directory_remove_file_monitors (NautilusDirectory *directory,
                                         NautilusFile      *file)
{
    GList *result, **list, *node, *next;
    Monitor *monitor;

    g_assert (NAUTILUS_IS_DIRECTORY (directory));
    g_assert (NAUTILUS_IS_FILE (file));
    g_assert (file->details->directory == directory);

    result = NULL;

    list = &directory->details->monitor_list;
    for (node = directory->details->monitor_list; node != NULL; node = next)
    {
        next = node->next;
        monitor = node->data;

        if (monitor->file == file)
        {
            *list = g_list_remove_link (*list, node);
            result = g_list_concat (node, result);
            request_counter_remove_request (directory->details->monitor_counters,
                                            monitor->request);
        }
    }

    /* XXX - do we need to remove anything from the work queue? */

    nautilus_directory_async_state_changed (directory);

    return (FileMonitors *) result;
}
