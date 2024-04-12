void FrameLoaderClient::dispatchWillSendRequest(WebCore::DocumentLoader* loader, unsigned long identifier, ResourceRequest& request, const ResourceResponse& redirectResponse)
{
    GOwnPtr<WebKitNetworkResponse> networkResponse(0);

    if (redirectResponse.isNull())
        static_cast<WebKit::DocumentLoader*>(loader)->increaseLoadCount(identifier);
    else
        networkResponse.set(webkit_network_response_new_with_core_response(redirectResponse));

    WebKitWebView* webView = getViewFromFrame(m_frame);
    GOwnPtr<gchar> identifierString(toString(identifier));
    WebKitWebResource* webResource = webkit_web_view_get_resource(webView, identifierString.get());
    GOwnPtr<WebKitNetworkRequest> networkRequest(webkit_network_request_new_with_core_request(request));

    if (!redirectResponse.isNull()) {
        g_free(webResource->priv->uri);
        webResource->priv->uri = g_strdup(request.url().string().utf8().data());
    }
    
    g_signal_emit_by_name(webView, "resource-request-starting", m_frame, webResource, networkRequest.get(), networkResponse.get());

    SoupMessage* message = webkit_network_request_get_message(networkRequest.get());
    if (!message) {
        request.setURL(KURL(KURL(), String::fromUTF8(webkit_network_request_get_uri(networkRequest.get()))));
        return;
    }

    request.updateFromSoupMessage(message);
}
