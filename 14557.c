_our_safe_malloc(size_t len, const char *funcname, const int line, const char *file)
{
    u_char *ptr;

    if ((ptr = malloc(len)) == NULL) {
        fprintf(stderr, "ERROR in %s:%s() line %d: Unable to malloc() %zu bytes/n",
                file, funcname, line, len);
        exit(-1);
    }

    /* zero memory */
    memset(ptr, 0, len);

    /* wrapped inside an #ifdef for better performance */
    dbgx(5, "Malloc'd %zu bytes in %s:%s() line %d", len, file, funcname, line);

    return (void *)ptr;
}
