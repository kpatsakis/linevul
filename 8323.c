WebKitWebFrame* webkit_web_frame_find_frame(WebKitWebFrame* frame, const gchar* name)
{
    g_return_val_if_fail(WEBKIT_IS_WEB_FRAME(frame), NULL);
    g_return_val_if_fail(name, NULL);

    Frame* coreFrame = core(frame);
    if (!coreFrame)
        return NULL;

    String nameString = String::fromUTF8(name);
    return kit(coreFrame->tree()->find(AtomicString(nameString)));
}
