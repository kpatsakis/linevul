void WebPageProxy::didReceiveTitleForFrame(uint64_t frameID, const String& title, CoreIPC::ArgumentDecoder* arguments)
{
    RefPtr<APIObject> userData;
    WebContextUserMessageDecoder messageDecoder(userData, context());
    if (!arguments->decode(messageDecoder))
        return;

    WebFrameProxy* frame = process()->webFrame(frameID);
    MESSAGE_CHECK(frame);

    frame->didChangeTitle(title);
    
    m_loaderClient.didReceiveTitleForFrame(this, title, frame, userData.get());
}
