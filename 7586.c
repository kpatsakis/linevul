delete_file_recursively (GFile          *file,
                         GCancellable   *cancellable,
                         DeleteCallback  callback,
                         gpointer        callback_data)
{
    gboolean success;
    g_autoptr (GError) error = NULL;

    do
    {
        g_autoptr (GFileEnumerator) enumerator = NULL;

        success = g_file_delete (file, cancellable, &error);
        if (success ||
            !g_error_matches (error, G_IO_ERROR, G_IO_ERROR_NOT_EMPTY))
        {
            break;
        }

        g_clear_error (&error);

        enumerator = g_file_enumerate_children (file,
                                                G_FILE_ATTRIBUTE_STANDARD_NAME,
                                                G_FILE_QUERY_INFO_NONE,
                                                cancellable, &error);

        if (enumerator)
        {
            GFileInfo *info;

            success = TRUE;

            info = g_file_enumerator_next_file (enumerator,
                                                cancellable,
                                                &error);

            while (info != NULL)
            {
                g_autoptr (GFile) child = NULL;

                child = g_file_enumerator_get_child (enumerator, info);

                success = success && delete_file_recursively (child,
                                                              cancellable,
                                                              callback,
                                                              callback_data);

                g_object_unref (info);

                info = g_file_enumerator_next_file (enumerator,
                                                    cancellable,
                                                    &error);
            }
        }

        if (error != NULL)
        {
            success = FALSE;
        }
    }
    while (success);

    if (callback)
    {
        callback (file, error, callback_data);
    }

    return success;
}
