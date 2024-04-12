static void search_timeout(GtkEntry *entry)
{
    /* this little hack makes the search start searching after 500 milisec after
     * user stops writing into entry box
     * if this part is removed, then the search will be started on every
     * change of the search entry
     */
    if (g_timeout != 0)
        g_source_remove(g_timeout);
    g_timeout = g_timeout_add(500, &highlight_search_on_timeout, (gpointer)entry);
}
