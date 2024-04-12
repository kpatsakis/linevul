new_files_state_unref (NewFilesState *state)
{
    state->count--;

    if (state->count == 0)
    {
        if (state->directory)
        {
            state->directory->details->new_files_in_progress =
                g_list_remove (state->directory->details->new_files_in_progress,
                               state);
        }

        g_object_unref (state->cancellable);
        g_free (state);
    }
}
