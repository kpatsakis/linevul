v8::Local<v8::Context> V8Proxy::mainWorldContext(Frame* frame)
{
    V8Proxy* proxy = retrieve(frame);
    if (!proxy)
        return v8::Local<v8::Context>();

    return proxy->mainWorldContext();
}
