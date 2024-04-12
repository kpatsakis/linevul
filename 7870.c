lacks_link_info (NautilusFile *file)
{
    if (file->details->file_info_is_up_to_date &&
        !file->details->link_info_is_up_to_date)
    {
        if (nautilus_file_is_nautilus_link (file))
        {
            return TRUE;
        }
        else
        {
            link_info_done (file->details->directory, file, NULL, NULL, NULL, FALSE, FALSE);
            return FALSE;
        }
    }
    else
    {
        return FALSE;
    }
}
