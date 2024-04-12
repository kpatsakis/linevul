ResourceError FrameLoaderClient::pluginWillHandleLoadError(const ResourceResponse& response)
{
    return ResourceError(g_quark_to_string(WEBKIT_PLUGIN_ERROR), WEBKIT_PLUGIN_ERROR_WILL_HANDLE_LOAD,
                         response.url().string(), _("Plugin will handle load"));
}
