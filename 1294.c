mime_list_one (MimeListState *state,
               GFileInfo     *info)
{
    const char *mime_type;

    if (should_skip_file (NULL, info))
    {
        g_object_unref (info);
        return;
    }

    mime_type = g_file_info_get_content_type (info);
    if (mime_type != NULL)
    {
        istr_set_insert (state->mime_list_hash, mime_type);
    }
}
