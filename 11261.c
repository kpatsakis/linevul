void V8Window::eventAttributeGetterCustom(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
    v8::Handle<v8::Object> holder = info.This()->FindInstanceInPrototypeChain(V8Window::GetTemplate(info.GetIsolate(), worldTypeInMainThread(info.GetIsolate())));
    if (holder.IsEmpty())
        return;

    Frame* frame = V8Window::toNative(holder)->frame();
    ExceptionState es(info.GetIsolate());
    if (!BindingSecurity::shouldAllowAccessToFrame(frame, es)) {
        es.throwIfNeeded();
        return;
    }

    ASSERT(frame);
    v8::Local<v8::Context> context = frame->script()->currentWorldContext();
    if (context.IsEmpty())
        return;

    v8::Handle<v8::String> eventSymbol = V8HiddenPropertyName::event(info.GetIsolate());
    v8::Handle<v8::Value> jsEvent = context->Global()->GetHiddenValue(eventSymbol);
    if (jsEvent.IsEmpty())
        return;
    v8SetReturnValue(info, jsEvent);
}
