f (const char *format,
   ...)
{
    va_list va;
    char *res;

    va_start (va, format);
    res = eel_strdup_vprintf_with_custom (handlers, format, va);
    va_end (va);

    return res;
}
