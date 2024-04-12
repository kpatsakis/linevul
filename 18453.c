get_link_name (const char *name,
               int         count,
               int         max_length)
{
    const char *format;
    char *result;
    int unshortened_length;
    gboolean use_count;

    g_assert (name != NULL);

    if (count < 0)
    {
        g_warning ("bad count in get_link_name");
        count = 0;
    }

    if (count <= 2)
    {
        /* Handle special cases for low numbers.
         * Perhaps for some locales we will need to add more.
         */
        switch (count)
        {
            default:
            {
                g_assert_not_reached ();
                /* fall through */
            }

            case 0:
            {
                /* duplicate original file name */
                format = "%s";
            }
            break;

            case 1:
            {
                /* appended to new link file */
                format = _("Link to %s");
            }
            break;

            case 2:
            {
                /* appended to new link file */
                format = _("Another link to %s");
            }
            break;
        }

        use_count = FALSE;
    }
    else
    {
        /* Handle special cases for the first few numbers of each ten.
         * For locales where getting this exactly right is difficult,
         * these can just be made all the same as the general case below.
         */
        switch (count % 10)
        {
            case 1:
            {
                /* Localizers: Feel free to leave out the "st" suffix
                 * if there's no way to do that nicely for a
                 * particular language.
                 */
                format = _("%'dst link to %s");
            }
            break;

            case 2:
            {
                /* appended to new link file */
                format = _("%'dnd link to %s");
            }
            break;

            case 3:
            {
                /* appended to new link file */
                format = _("%'drd link to %s");
            }
            break;

            default:
            {
                /* appended to new link file */
                format = _("%'dth link to %s");
            }
            break;
        }

        use_count = TRUE;
    }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
    if (use_count)
    {
        result = g_strdup_printf (format, count, name);
    }
    else
    {
        result = g_strdup_printf (format, name);
    }

    if (max_length > 0 && (unshortened_length = strlen (result)) > max_length)
    {
        char *new_name;

        new_name = shorten_utf8_string (name, unshortened_length - max_length);
        if (new_name)
        {
            g_free (result);

            if (use_count)
            {
                result = g_strdup_printf (format, count, new_name);
            }
            else
            {
                result = g_strdup_printf (format, new_name);
            }

            g_assert (strlen (result) <= max_length);
            g_free (new_name);
        }
    }
#pragma GCC diagnostic pop
    return result;
}
