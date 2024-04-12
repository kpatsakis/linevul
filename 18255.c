v8::Handle<v8::Object> V8TestNamedConstructor::wrapSlow(PassRefPtr<TestNamedConstructor> impl, v8::Isolate* isolate)
{
    v8::Handle<v8::Object> wrapper;
    V8Proxy* proxy = 0;
    wrapper = V8DOMWrapper::instantiateV8Object(proxy, &info, impl.get());
    if (UNLIKELY(wrapper.IsEmpty()))
        return wrapper;

    v8::Persistent<v8::Object> wrapperHandle = v8::Persistent<v8::Object>::New(wrapper);

    if (!hasDependentLifetime)
        wrapperHandle.MarkIndependent();
    V8DOMWrapper::setJSWrapperForActiveDOMObject(impl, wrapperHandle, isolate);
    return wrapper;
}
