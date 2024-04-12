filesystem_info_state_free (FilesystemInfoState *state)
{
    g_object_unref (state->cancellable);
    g_free (state);
}
