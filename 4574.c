static v8::Handle<v8::Value> removeEventListenerCallback(const v8::Arguments& args)
{
    INC_STATS("DOM.TestObj.removeEventListener()");
    RefPtr<EventListener> listener = V8DOMWrapper::getEventListener(args[1], false, ListenerFindOnly);
    if (listener) {
        V8TestObj::toNative(args.Holder())->removeEventListener(v8ValueToAtomicWebCoreString(args[0]), listener.get(), args[2]->BooleanValue());
        removeHiddenDependency(args.Holder(), args[1], V8TestObj::eventListenerCacheIndex);
    }
    return v8::Undefined();
}
