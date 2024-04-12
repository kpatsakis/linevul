G_CONST_RETURN gchar* webkit_web_frame_get_name(WebKitWebFrame* frame)
{
    g_return_val_if_fail(WEBKIT_IS_WEB_FRAME(frame), NULL);

    WebKitWebFramePrivate* priv = frame->priv;

    if (priv->name)
        return priv->name;

    Frame* coreFrame = core(frame);
    if (!coreFrame)
        return "";

    String string = coreFrame->tree()->name();
    priv->name = g_strdup(string.utf8().data());
    return priv->name;
}
