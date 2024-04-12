can_delete_without_confirm (GFile *file)
{
    if (g_file_has_uri_scheme (file, "burn") ||
        g_file_has_uri_scheme (file, "recent") ||
        g_file_has_uri_scheme (file, "x-nautilus-desktop"))
    {
        return TRUE;
    }

    return FALSE;
}
