void WebPageProxy::didFirstVisuallyNonEmptyLayoutForFrame(uint64_t frameID, CoreIPC::ArgumentDecoder* arguments)
{
    RefPtr<APIObject> userData;
    WebContextUserMessageDecoder messageDecoder(userData, context());
    if (!arguments->decode(messageDecoder))
        return;

    WebFrameProxy* frame = process()->webFrame(frameID);
    MESSAGE_CHECK(frame);

    m_loaderClient.didFirstVisuallyNonEmptyLayoutForFrame(this, frame, userData.get());
}
