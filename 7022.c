packet_stats(const tcpreplay_stats_t *stats)
{
    struct timeval diff;
    COUNTER diff_us;
    COUNTER bytes_sec = 0;
    u_int32_t bytes_sec_10ths = 0;
    COUNTER mb_sec = 0;
    u_int32_t mb_sec_100ths = 0;
    u_int32_t mb_sec_1000ths = 0;
    COUNTER pkts_sec = 0;
    u_int32_t pkts_sec_100ths = 0;

    timersub(&stats->end_time, &stats->start_time, &diff);
    diff_us = TIMEVAL_TO_MICROSEC(&diff);

    if (diff_us && stats->pkts_sent && stats->bytes_sent) {
        COUNTER bytes_sec_X10;
        COUNTER pkts_sec_X100;
        COUNTER mb_sec_X1000;
        COUNTER mb_sec_X100;

        if (stats->bytes_sent > 1000 * 1000 * 1000 && diff_us > 1000 * 1000) {
            bytes_sec_X10 = (stats->bytes_sent * 10 * 1000) / (diff_us / 1000);
            pkts_sec_X100 = (stats->pkts_sent * 100 * 1000) / (diff_us / 1000);
         } else {
            bytes_sec_X10 = (stats->bytes_sent * 10 * 1000 * 1000) / diff_us;
            pkts_sec_X100 = (stats->pkts_sent * 100 * 1000 * 1000) / diff_us;
         }

        bytes_sec = bytes_sec_X10 / 10;
        bytes_sec_10ths = bytes_sec_X10 % 10;

        mb_sec_X1000 = (bytes_sec * 8) / 1000;
        mb_sec_X100 = mb_sec_X1000 / 10;
        mb_sec = mb_sec_X1000 / 1000;
        mb_sec_100ths = mb_sec_X100 % 100;
        mb_sec_1000ths = mb_sec_X1000 % 1000;

        pkts_sec = pkts_sec_X100 / 100;
        pkts_sec_100ths = pkts_sec_X100 % 100;
    }

    if (diff_us >= 1000 * 1000)
        printf("Actual: " COUNTER_SPEC " packets (" COUNTER_SPEC " bytes) sent in %zd.%02zd seconds\n",
                stats->pkts_sent, stats->bytes_sent, (ssize_t)diff.tv_sec, (ssize_t)(diff.tv_usec / (10 * 1000)));
    else
        printf("Actual: " COUNTER_SPEC " packets (" COUNTER_SPEC " bytes) sent in %zd.%06zd seconds\n",
                stats->pkts_sent, stats->bytes_sent, (ssize_t)diff.tv_sec, (ssize_t)diff.tv_usec);


    if (mb_sec >= 1)
        printf("Rated: %llu.%1u Bps, %llu.%02u Mbps, %llu.%02u pps\n",
               bytes_sec, bytes_sec_10ths, mb_sec, mb_sec_100ths, pkts_sec, pkts_sec_100ths);
    else
        printf("Rated: %llu.%1u Bps, %llu.%03u Mbps, %llu.%02u pps\n",
               bytes_sec, bytes_sec_10ths, mb_sec, mb_sec_1000ths, pkts_sec, pkts_sec_100ths);
    fflush(NULL);
    
    if (stats->failed)
        printf("Failed write attempts: " COUNTER_SPEC "\n",
                stats->failed);
}
