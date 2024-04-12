guint webkit_web_frame_get_pending_unload_event_count(WebKitWebFrame* frame)
{
    g_return_val_if_fail(WEBKIT_IS_WEB_FRAME(frame), 0);

    return core(frame)->domWindow()->pendingUnloadEventListeners();
}
