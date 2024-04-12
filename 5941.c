int errwrite_nomem(const char *str, int len)
{
    return errwrite(mem_err_print, str, len);
}
