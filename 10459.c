static void removeEventListenerMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "removeEventListener", "TestObject", info.Holder(), info.GetIsolate());
    EventTarget* impl = V8TestObject::toNative(info.Holder());
    if (DOMWindow* window = impl->toDOMWindow()) {
        if (!BindingSecurity::shouldAllowAccessToFrame(info.GetIsolate(), window->frame(), exceptionState)) {
            exceptionState.throwIfNeeded();
            return;
        }
        if (!window->document())
            return;
    }
    RefPtr<EventListener> listener = V8EventListenerList::getEventListener(info[1], false, ListenerFindOnly);
    if (listener) {
        V8TRYCATCH_FOR_V8STRINGRESOURCE_VOID(V8StringResource<WithNullCheck>, eventName, info[0]);
        impl->removeEventListener(eventName, listener.get(), info[2]->BooleanValue());
        if (!impl->toNode())
            removeHiddenValueFromArray(info.Holder(), info[1], V8TestObject::eventListenerCacheIndex, info.GetIsolate());
    }
}
