got_filesystem_info (FilesystemInfoState *state,
                     GFileInfo           *info)
{
    NautilusDirectory *directory;
    NautilusFile *file;
    const char *filesystem_type;

    /* careful here, info may be NULL */

    directory = nautilus_directory_ref (state->directory);

    state->directory->details->filesystem_info_state = NULL;
    async_job_end (state->directory, "filesystem info");

    file = nautilus_file_ref (state->file);

    file->details->filesystem_info_is_up_to_date = TRUE;
    if (info != NULL)
    {
        file->details->filesystem_use_preview =
            g_file_info_get_attribute_uint32 (info, G_FILE_ATTRIBUTE_FILESYSTEM_USE_PREVIEW);
        file->details->filesystem_readonly =
            g_file_info_get_attribute_boolean (info, G_FILE_ATTRIBUTE_FILESYSTEM_READONLY);
        filesystem_type = g_file_info_get_attribute_string (info, G_FILE_ATTRIBUTE_FILESYSTEM_TYPE);
        if (g_strcmp0 (eel_ref_str_peek (file->details->filesystem_type), filesystem_type) != 0)
        {
            eel_ref_str_unref (file->details->filesystem_type);
            file->details->filesystem_type = eel_ref_str_get_unique (filesystem_type);
        }
    }

    nautilus_directory_async_state_changed (directory);
    nautilus_file_changed (file);

    nautilus_file_unref (file);

    nautilus_directory_unref (directory);

    filesystem_info_state_free (state);
}
