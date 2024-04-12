file_deleted_callback (GFile    *file,
                       GError   *error,
                       gpointer  callback_data)
{
    DeleteData *data = callback_data;
    CommonJob *job;
    SourceInfo *source_info;
    TransferInfo *transfer_info;
    GFileType file_type;
    char *primary;
    char *secondary;
    char *details = NULL;
    int response;

    job = data->job;
    source_info = data->source_info;
    transfer_info = data->transfer_info;

    data->transfer_info->num_files++;

    if (error == NULL)
    {
        nautilus_file_changes_queue_file_removed (file);
        report_delete_progress (data->job, data->source_info, data->transfer_info);

        return;
    }

    if (job_aborted (job) ||
        job->skip_all_error ||
        should_skip_file (job, file) ||
        should_skip_readdir_error (job, file))
    {
        return;
    }

    primary = f (_("Error while deleting."));

    file_type = g_file_query_file_type (file,
                                        G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS,
                                        job->cancellable);

    if (file_type == G_FILE_TYPE_DIRECTORY)
    {
        secondary = IS_IO_ERROR (error, PERMISSION_DENIED) ?
                    f (_("There was an error deleting the folder “%B”."),
                       file) :
                    f (_("You do not have sufficient permissions to delete the folder “%B”."),
                       file);
    }
    else
    {
        secondary = IS_IO_ERROR (error, PERMISSION_DENIED) ?
                    f (_("There was an error deleting the file “%B”."),
                       file) :
                    f (_("You do not have sufficient permissions to delete the file “%B”."),
                       file);
    }

    details = error->message;

    response = run_cancel_or_skip_warning (job,
                                           primary,
                                           secondary,
                                           details,
                                           source_info->num_files,
                                           source_info->num_files - transfer_info->num_files);

    if (response == 0 || response == GTK_RESPONSE_DELETE_EVENT)
    {
        abort_job (job);
    }
    else if (response == 1)
    {
        /* skip all */
        job->skip_all_error = TRUE;
    }
}
