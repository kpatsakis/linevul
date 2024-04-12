GtkPolicyType webkit_web_frame_get_horizontal_scrollbar_policy(WebKitWebFrame* frame)
{
    g_return_val_if_fail(WEBKIT_IS_WEB_FRAME(frame), GTK_POLICY_AUTOMATIC);

    Frame* coreFrame = core(frame);
    FrameView* view = coreFrame->view();
    if (!view)
        return GTK_POLICY_AUTOMATIC;

    ScrollbarMode hMode = view->horizontalScrollbarMode();

    if (hMode == ScrollbarAlwaysOn)
        return GTK_POLICY_ALWAYS;

    if (hMode == ScrollbarAlwaysOff)
        return GTK_POLICY_NEVER;

    return GTK_POLICY_AUTOMATIC;
}
