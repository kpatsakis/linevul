void WebPageProxy::getWebArchiveOfFrame(WebFrameProxy* frame, PassRefPtr<DataCallback> prpCallback)
{
    RefPtr<DataCallback> callback = prpCallback;
    if (!isValid()) {
        callback->invalidate();
        return;
    }
    
    uint64_t callbackID = callback->callbackID();
    m_dataCallbacks.set(callbackID, callback.get());
    process()->send(Messages::WebPage::GetWebArchiveOfFrame(frame->frameID(), callbackID), m_pageID);
}
