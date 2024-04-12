filesystem_info_stop (NautilusDirectory *directory)
{
    NautilusFile *file;

    if (directory->details->filesystem_info_state != NULL)
    {
        file = directory->details->filesystem_info_state->file;

        if (file != NULL)
        {
            g_assert (NAUTILUS_IS_FILE (file));
            g_assert (file->details->directory == directory);
            if (is_needy (file,
                          lacks_filesystem_info,
                          REQUEST_FILESYSTEM_INFO))
            {
                return;
            }
        }

        /* The filesystem info is not wanted, so stop it. */
        filesystem_info_cancel (directory);
    }
}
