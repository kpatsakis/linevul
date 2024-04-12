int format_date_time(struct timeval *when, char *buf, size_t len)
{
    struct tm *tm;
    char tmp[64];

    assert(len);

    tm = localtime(&when->tv_sec);
    if (!tm)
        return -1;

    strftime(tmp, sizeof tmp, "%Y-%m-%d %H:%M:%S.%%06u", tm);
    return snprintf(buf, len, tmp, when->tv_usec);
}
