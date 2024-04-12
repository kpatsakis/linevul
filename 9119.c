static int uniq_field_values(void *d, const char *key, const char *val)
{
    apr_array_header_t *values;
    char *start;
    char *e;
    char **strpp;
    int  i;

    values = (apr_array_header_t *)d;

    e = apr_pstrdup(values->pool, val);

    do {
        /* Find a non-empty fieldname */

        while (*e == ',' || apr_isspace(*e)) {
            ++e;
        }
        if (*e == '\0') {
            break;
        }
        start = e;
        while (*e != '\0' && *e != ',' && !apr_isspace(*e)) {
            ++e;
        }
        if (*e != '\0') {
            *e++ = '\0';
        }

        /* Now add it to values if it isn't already represented.
         * Could be replaced by a ap_array_strcasecmp() if we had one.
         */
        for (i = 0, strpp = (char **) values->elts; i < values->nelts;
             ++i, ++strpp) {
            if (*strpp && strcasecmp(*strpp, start) == 0) {
                break;
            }
        }
        if (i == values->nelts) {  /* if not found */
            *(char **)apr_array_push(values) = start;
        }
    } while (*e != '\0');

    return 1;
}
