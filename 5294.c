void WebPageProxy::forceRepaint(PassRefPtr<VoidCallback> prpCallback)
{
    RefPtr<VoidCallback> callback = prpCallback;
    if (!isValid()) {
        callback->invalidate();
        return;
    }

    uint64_t callbackID = callback->callbackID();
    m_voidCallbacks.set(callbackID, callback.get());
    process()->send(Messages::WebPage::ForceRepaint(callbackID), m_pageID); 
}
