logger_day_changed_signal_cb (const void *pointer, void *data,
                              const char *signal,
                              const char *type_data, void *signal_data)
{
    /* make C compiler happy */
    (void) pointer;
    (void) data;
    (void) signal;
    (void) type_data;
    (void) signal_data;

    logger_adjust_log_filenames ();

    return WEECHAT_RC_OK;
}
