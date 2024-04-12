link_info_start (NautilusDirectory *directory,
                 NautilusFile      *file,
                 gboolean          *doing_io)
{
    GFile *location;
    gboolean nautilus_style_link;
    LinkInfoReadState *state;

    if (directory->details->link_info_read_state != NULL)
    {
        *doing_io = TRUE;
        return;
    }

    if (!is_needy (file,
                   lacks_link_info,
                   REQUEST_LINK_INFO))
    {
        return;
    }
    *doing_io = TRUE;

    /* Figure out if it is a link. */
    nautilus_style_link = nautilus_file_is_nautilus_link (file);
    location = nautilus_file_get_location (file);

    /* If it's not a link we are done. If it is, we need to read it. */
    if (!nautilus_style_link)
    {
        link_info_done (directory, file, NULL, NULL, NULL, FALSE, FALSE);
    }
    else
    {
        if (!async_job_start (directory, "link info"))
        {
            g_object_unref (location);
            return;
        }

        state = g_new0 (LinkInfoReadState, 1);
        state->directory = directory;
        state->file = file;
        state->cancellable = g_cancellable_new ();

        directory->details->link_info_read_state = state;

        g_file_load_contents_async (location,
                                    state->cancellable,
                                    link_info_nautilus_link_read_callback,
                                    state);
    }
    g_object_unref (location);
}
