static int http_get_line(HTTPContext *s, char *line, int line_size)
{
    int ch;
    char *q;

    q = line;
    for (;;) {
        ch = http_getc(s);
        if (ch < 0)
            return ch;
        if (ch == '\n') {
            /* process line */
            if (q > line && q[-1] == '\r')
                q--;
            *q = '\0';

            return 0;
        } else {
            if ((q - line) < line_size - 1)
                *q++ = ch;
        }
    }
}
