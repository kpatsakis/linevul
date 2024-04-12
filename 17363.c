custom_full_name_to_string (char    *format,
                            va_list  va)
{
    GFile *file;

    file = va_arg (va, GFile *);

    return g_file_get_parse_name (file);
}
