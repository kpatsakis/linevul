scan_file (GFile      *file,
           SourceInfo *source_info,
           CommonJob  *job,
           GHashTable *scanned)
{
    GFileInfo *info;
    GError *error;
    GQueue *dirs;
    GFile *dir;
    char *primary;
    char *secondary;
    char *details;
    int response;

    dirs = g_queue_new ();

retry:
    error = NULL;
    info = g_file_query_info (file,
                              G_FILE_ATTRIBUTE_STANDARD_TYPE ","
                              G_FILE_ATTRIBUTE_STANDARD_SIZE,
                              G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS,
                              job->cancellable,
                              &error);

    if (info)
    {
        g_autofree char *file_uri = NULL;

        file_uri = g_file_get_uri (file);
        if (!g_hash_table_contains (scanned, file_uri))
        {
            g_hash_table_add (scanned, g_strdup (file_uri));

            count_file (info, job, source_info);

            /* trashing operation doesn't recurse */
            if (g_file_info_get_file_type (info) == G_FILE_TYPE_DIRECTORY &&
                source_info->op != OP_KIND_TRASH)
            {
                g_queue_push_head (dirs, g_object_ref (file));
            }
        }
        g_object_unref (info);
    }
    else if (job->skip_all_error)
    {
        g_error_free (error);
        skip_file (job, file);
    }
    else if (IS_IO_ERROR (error, CANCELLED))
    {
        g_error_free (error);
    }
    else
    {
        primary = get_scan_primary (source_info->op);
        details = NULL;

        if (IS_IO_ERROR (error, PERMISSION_DENIED))
        {
            secondary = f (_("The file “%B” cannot be handled because you do not have "
                             "permissions to read it."), file);
        }
        else
        {
            secondary = f (_("There was an error getting information about “%B”."), file);
            details = error->message;
        }
        /* set show_all to TRUE here, as we don't know how many
         * files we'll end up processing yet.
         */
        response = run_warning (job,
                                primary,
                                secondary,
                                details,
                                TRUE,
                                CANCEL, SKIP_ALL, SKIP, RETRY,
                                NULL);

        g_error_free (error);

        if (response == 0 || response == GTK_RESPONSE_DELETE_EVENT)
        {
            abort_job (job);
        }
        else if (response == 1 || response == 2)
        {
            if (response == 1)
            {
                job->skip_all_error = TRUE;
            }
            skip_file (job, file);
        }
        else if (response == 3)
        {
            goto retry;
        }
        else
        {
            g_assert_not_reached ();
        }
    }

    while (!job_aborted (job) &&
           (dir = g_queue_pop_head (dirs)) != NULL)
    {
        scan_dir (dir, source_info, job, dirs, scanned);
        g_object_unref (dir);
    }

    /* Free all from queue if we exited early */
    g_queue_foreach (dirs, (GFunc) g_object_unref, NULL);
    g_queue_free (dirs);
}
