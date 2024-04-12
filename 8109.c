static void webkit_web_frame_get_property(GObject* object, guint prop_id, GValue* value, GParamSpec* pspec)
{
    WebKitWebFrame* frame = WEBKIT_WEB_FRAME(object);

    switch(prop_id) {
    case PROP_NAME:
        g_value_set_string(value, webkit_web_frame_get_name(frame));
        break;
    case PROP_TITLE:
        g_value_set_string(value, webkit_web_frame_get_title(frame));
        break;
    case PROP_URI:
        g_value_set_string(value, webkit_web_frame_get_uri(frame));
        break;
    case PROP_LOAD_STATUS:
        g_value_set_enum(value, webkit_web_frame_get_load_status(frame));
        break;
    case PROP_HORIZONTAL_SCROLLBAR_POLICY:
        g_value_set_enum(value, webkit_web_frame_get_horizontal_scrollbar_policy(frame));
        break;
    case PROP_VERTICAL_SCROLLBAR_POLICY:
        g_value_set_enum(value, webkit_web_frame_get_vertical_scrollbar_policy(frame));
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
        break;
    }
}
