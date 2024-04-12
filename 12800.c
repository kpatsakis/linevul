void V8Window::eventAttributeSetterCustom(v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
    LocalFrame* frame = toLocalDOMWindow(V8Window::toImpl(info.Holder()))->frame();
    ExceptionState exceptionState(ExceptionState::SetterContext, "event", "Window", info.Holder(), info.GetIsolate());
    if (!BindingSecurity::shouldAllowAccessToFrame(info.GetIsolate(), frame, exceptionState)) {
        exceptionState.throwIfNeeded();
        return;
    }

    ASSERT(frame);
    v8::Local<v8::Context> context = toV8Context(frame, DOMWrapperWorld::current(info.GetIsolate()));
    if (context.IsEmpty())
        return;

    V8HiddenValue::setHiddenValue(info.GetIsolate(), context->Global(), V8HiddenValue::event(info.GetIsolate()), value);
}
