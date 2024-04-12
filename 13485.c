link_info_stop (NautilusDirectory *directory)
{
    NautilusFile *file;

    if (directory->details->link_info_read_state != NULL)
    {
        file = directory->details->link_info_read_state->file;

        if (file != NULL)
        {
            g_assert (NAUTILUS_IS_FILE (file));
            g_assert (file->details->directory == directory);
            if (is_needy (file,
                          lacks_link_info,
                          REQUEST_LINK_INFO))
            {
                return;
            }
        }

        /* The link info is not wanted, so stop it. */
        link_info_cancel (directory);
    }
}
