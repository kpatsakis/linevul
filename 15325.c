void m4vdec_dprintf(char *format, ...)
{
 FILE *log_fp;
    va_list args;
    va_start(args, format);

 /* open the log file */
    log_fp = fopen("\\mp4dec_log.txt", "a+");
 if (log_fp == NULL) return;
 /* output the message */
    vfprintf(log_fp, format, args);
    fclose(log_fp);

    va_end(args);
}
