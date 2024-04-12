set_permissions_file (SetPermissionsJob *job,
                      GFile             *file,
                      GFileInfo         *info)
{
    CommonJob *common;
    GFileInfo *child_info;
    gboolean free_info;
    guint32 current;
    guint32 value;
    guint32 mask;
    GFileEnumerator *enumerator;
    GFile *child;

    common = (CommonJob *) job;

    nautilus_progress_info_pulse_progress (common->progress);

    free_info = FALSE;
    if (info == NULL)
    {
        free_info = TRUE;
        info = g_file_query_info (file,
                                  G_FILE_ATTRIBUTE_STANDARD_TYPE ","
                                  G_FILE_ATTRIBUTE_UNIX_MODE,
                                  G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS,
                                  common->cancellable,
                                  NULL);
        /* Ignore errors */
        if (info == NULL)
        {
            return;
        }
    }

    if (g_file_info_get_file_type (info) == G_FILE_TYPE_DIRECTORY)
    {
        value = job->dir_permissions;
        mask = job->dir_mask;
    }
    else
    {
        value = job->file_permissions;
        mask = job->file_mask;
    }


    if (!job_aborted (common) &&
        g_file_info_has_attribute (info, G_FILE_ATTRIBUTE_UNIX_MODE))
    {
        current = g_file_info_get_attribute_uint32 (info, G_FILE_ATTRIBUTE_UNIX_MODE);

        if (common->undo_info != NULL)
        {
            nautilus_file_undo_info_rec_permissions_add_file (NAUTILUS_FILE_UNDO_INFO_REC_PERMISSIONS (common->undo_info),
                                                              file, current);
        }

        current = (current & ~mask) | value;

        g_file_set_attribute_uint32 (file, G_FILE_ATTRIBUTE_UNIX_MODE,
                                     current, G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS,
                                     common->cancellable, NULL);
    }

    if (!job_aborted (common) &&
        g_file_info_get_file_type (info) == G_FILE_TYPE_DIRECTORY)
    {
        enumerator = g_file_enumerate_children (file,
                                                G_FILE_ATTRIBUTE_STANDARD_NAME ","
                                                G_FILE_ATTRIBUTE_STANDARD_TYPE ","
                                                G_FILE_ATTRIBUTE_UNIX_MODE,
                                                G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS,
                                                common->cancellable,
                                                NULL);
        if (enumerator)
        {
            while (!job_aborted (common) &&
                   (child_info = g_file_enumerator_next_file (enumerator, common->cancellable, NULL)) != NULL)
            {
                child = g_file_get_child (file,
                                          g_file_info_get_name (child_info));
                set_permissions_file (job, child, child_info);
                g_object_unref (child);
                g_object_unref (child_info);
            }
            g_file_enumerator_close (enumerator, common->cancellable, NULL);
            g_object_unref (enumerator);
        }
    }
    if (free_info)
    {
        g_object_unref (info);
    }
}
