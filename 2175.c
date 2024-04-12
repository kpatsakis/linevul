extension_info_start (NautilusDirectory *directory,
                      NautilusFile      *file,
                      gboolean          *doing_io)
{
    NautilusInfoProvider *provider;
    NautilusOperationResult result;
    NautilusOperationHandle *handle;
    GClosure *update_complete;

    if (directory->details->extension_info_in_progress != NULL)
    {
        *doing_io = TRUE;
        return;
    }

    if (!is_needy (file, lacks_extension_info, REQUEST_EXTENSION_INFO))
    {
        return;
    }
    *doing_io = TRUE;

    if (!async_job_start (directory, "extension info"))
    {
        return;
    }

    provider = file->details->pending_info_providers->data;

    update_complete = g_cclosure_new (G_CALLBACK (info_provider_callback),
                                      directory,
                                      NULL);
    g_closure_set_marshal (update_complete,
                           g_cclosure_marshal_generic);

    result = nautilus_info_provider_update_file_info
                 (provider,
                 NAUTILUS_FILE_INFO (file),
                 update_complete,
                 &handle);

    g_closure_unref (update_complete);

    if (result == NAUTILUS_OPERATION_COMPLETE ||
        result == NAUTILUS_OPERATION_FAILED)
    {
        finish_info_provider (directory, file, provider);
        async_job_end (directory, "extension info");
    }
    else
    {
        directory->details->extension_info_in_progress = handle;
        directory->details->extension_info_provider = provider;
        directory->details->extension_info_file = file;
    }
}
