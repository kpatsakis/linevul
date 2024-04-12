void V8Window::toStringMethodCustom(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    v8::Handle<v8::Object> domWrapper = args.This()->FindInstanceInPrototypeChain(V8Window::GetTemplate(args.GetIsolate(), worldTypeInMainThread(args.GetIsolate())));
    if (domWrapper.IsEmpty()) {
        v8SetReturnValue(args, args.This()->ObjectProtoToString());
        return;
    }
    v8SetReturnValue(args, domWrapper->ObjectProtoToString());
}
