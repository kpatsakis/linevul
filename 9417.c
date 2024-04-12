location_list_from_uri_list (const GList *uris)
{
    const GList *l;
    GList *files;
    GFile *f;

    files = NULL;
    for (l = uris; l != NULL; l = l->next)
    {
        f = g_file_new_for_uri (l->data);
        files = g_list_prepend (files, f);
    }

    return g_list_reverse (files);
}
