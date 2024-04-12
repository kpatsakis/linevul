enumerate_children_callback (GObject      *source_object,
                             GAsyncResult *res,
                             gpointer      user_data)
{
    DirectoryLoadState *state;
    GFileEnumerator *enumerator;
    GError *error;

    state = user_data;

    if (state->directory == NULL)
    {
        /* Operation was cancelled. Bail out */
        directory_load_state_free (state);
        return;
    }

    error = NULL;
    enumerator = g_file_enumerate_children_finish (G_FILE (source_object),
                                                   res, &error);

    if (enumerator == NULL)
    {
        directory_load_done (state->directory, error);
        g_error_free (error);
        directory_load_state_free (state);
        return;
    }
    else
    {
        state->enumerator = enumerator;
        g_file_enumerator_next_files_async (state->enumerator,
                                            DIRECTORY_LOAD_ITEMS_PER_CALLBACK,
                                            G_PRIORITY_DEFAULT,
                                            state->cancellable,
                                            more_files_callback,
                                            state);
    }
}
