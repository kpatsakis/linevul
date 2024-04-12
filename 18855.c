extract_string_until (const char *original,
                      const char *until_substring)
{
    char *result;

    g_assert ((int) strlen (original) >= until_substring - original);
    g_assert (until_substring - original >= 0);

    result = g_malloc (until_substring - original + 1);
    strncpy (result, original, until_substring - original);
    result[until_substring - original] = '\0';

    return result;
}
