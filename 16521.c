void ServiceWorkerContainer::dispatchMessageEvent(WebPassOwnPtr<WebServiceWorker::Handle> handle, const WebString& message, const WebMessagePortChannelArray& webChannels)
{
    if (!getExecutionContext() || !getExecutionContext()->executingWindow())
        return;

    MessagePortArray* ports = MessagePort::toMessagePortArray(getExecutionContext(), webChannels);
    RefPtr<SerializedScriptValue> value = SerializedScriptValueFactory::instance().createFromWire(message);
    ServiceWorker* source = ServiceWorker::from(getExecutionContext(), handle.release());
    dispatchEvent(ServiceWorkerMessageEvent::create(ports, value, source, getExecutionContext()->getSecurityOrigin()->toString()));
}
