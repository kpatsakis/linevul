count_more_files_callback (GObject      *source_object,
                           GAsyncResult *res,
                           gpointer      user_data)
{
    DirectoryCountState *state;
    NautilusDirectory *directory;
    GError *error;
    GList *files;

    state = user_data;
    directory = state->directory;

    if (g_cancellable_is_cancelled (state->cancellable))
    {
        /* Operation was cancelled. Bail out */

        async_job_end (directory, "directory count");
        nautilus_directory_async_state_changed (directory);

        directory_count_state_free (state);

        return;
    }

    g_assert (directory->details->count_in_progress != NULL);
    g_assert (directory->details->count_in_progress == state);

    error = NULL;
    files = g_file_enumerator_next_files_finish (state->enumerator,
                                                 res, &error);

    state->file_count += count_non_skipped_files (files);

    if (files == NULL)
    {
        count_children_done (directory, state->count_file,
                             TRUE, state->file_count);
        directory_count_state_free (state);
    }
    else
    {
        g_file_enumerator_next_files_async (state->enumerator,
                                            DIRECTORY_LOAD_ITEMS_PER_CALLBACK,
                                            G_PRIORITY_DEFAULT,
                                            state->cancellable,
                                            count_more_files_callback,
                                            state);
    }

    g_list_free_full (files, g_object_unref);

    if (error)
    {
        g_error_free (error);
    }
}
