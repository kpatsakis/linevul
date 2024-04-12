static int run_event_gtk_ask_yes_no_save_result(const char *key, const char *msg, void *args)
{
    const int ret = run_ask_yes_no_save_result_dialog(key, msg, GTK_WINDOW(g_wnd_assistant));
    log_request_response_communication(msg, ret ? "YES" : "NO", (struct analyze_event_data *)args);
    return ret;
}
