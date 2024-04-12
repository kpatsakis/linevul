parse_previous_duplicate_name (const char  *name,
                               char       **name_base,
                               const char **suffix,
                               int         *count)
{
    const char *tag;

    g_assert (name[0] != '\0');

    *suffix = eel_filename_get_extension_offset (name);

    if (*suffix == NULL || (*suffix)[1] == '\0')
    {
        /* no suffix */
        *suffix = "";
    }

    tag = strstr (name, COPY_DUPLICATE_TAG);
    if (tag != NULL)
    {
        if (tag > *suffix)
        {
            /* handle case "foo. (copy)" */
            *suffix = "";
        }
        *name_base = extract_string_until (name, tag);
        *count = 1;
        return;
    }


    tag = strstr (name, ANOTHER_COPY_DUPLICATE_TAG);
    if (tag != NULL)
    {
        if (tag > *suffix)
        {
            /* handle case "foo. (another copy)" */
            *suffix = "";
        }
        *name_base = extract_string_until (name, tag);
        *count = 2;
        return;
    }


    /* Check to see if we got one of st, nd, rd, th. */
    tag = strstr (name, X11TH_COPY_DUPLICATE_TAG);

    if (tag == NULL)
    {
        tag = strstr (name, X12TH_COPY_DUPLICATE_TAG);
    }
    if (tag == NULL)
    {
        tag = strstr (name, X13TH_COPY_DUPLICATE_TAG);
    }

    if (tag == NULL)
    {
        tag = strstr (name, ST_COPY_DUPLICATE_TAG);
    }
    if (tag == NULL)
    {
        tag = strstr (name, ND_COPY_DUPLICATE_TAG);
    }
    if (tag == NULL)
    {
        tag = strstr (name, RD_COPY_DUPLICATE_TAG);
    }
    if (tag == NULL)
    {
        tag = strstr (name, TH_COPY_DUPLICATE_TAG);
    }

    /* If we got one of st, nd, rd, th, fish out the duplicate number. */
    if (tag != NULL)
    {
        /* localizers: opening parentheses to match the "th copy)" string */
        tag = strstr (name, _(" ("));
        if (tag != NULL)
        {
            if (tag > *suffix)
            {
                /* handle case "foo. (22nd copy)" */
                *suffix = "";
            }
            *name_base = extract_string_until (name, tag);
            /* localizers: opening parentheses of the "th copy)" string */
            if (sscanf (tag, _(" (%'d"), count) == 1)
            {
                if (*count < 1 || *count > 1000000)
                {
                    /* keep the count within a reasonable range */
                    *count = 0;
                }
                return;
            }
            *count = 0;
            return;
        }
    }


    *count = 0;
    if (**suffix != '\0')
    {
        *name_base = extract_string_until (name, *suffix);
    }
    else
    {
        *name_base = g_strdup (name);
    }
}
