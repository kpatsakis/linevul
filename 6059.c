nautilus_mime_activate_file (GtkWindow               *parent_window,
                             NautilusWindowSlot      *slot,
                             NautilusFile            *file,
                             const char              *launch_directory,
                             NautilusWindowOpenFlags  flags)
{
    GList *files;

    g_return_if_fail (NAUTILUS_IS_FILE (file));

    files = g_list_prepend (NULL, file);
    nautilus_mime_activate_files (parent_window, slot, files, launch_directory, flags, FALSE);
    g_list_free (files);
}
