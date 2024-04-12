static void die_if_data_is_missing(GHashTable *problem_info)
{
    gboolean missing_data = FALSE;
    gchar **pstring;
    static const gchar *const needed[] = {
        FILENAME_TYPE,
        FILENAME_REASON,
        /* FILENAME_BACKTRACE, - ECC errors have no such elements */
        /* FILENAME_EXECUTABLE, */
        NULL
    };

    for (pstring = (gchar**) needed; *pstring; pstring++)
    {
        if (!g_hash_table_lookup(problem_info, *pstring))
        {
            error_msg("Element '%s' is missing", *pstring);
            missing_data = TRUE;
        }
    }

    if (missing_data)
        error_msg_and_die("Some data is missing, aborting");
}
