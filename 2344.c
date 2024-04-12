static void promiseAttributeAttributeSetter(v8::Local<v8::Value> jsValue, const v8::PropertyCallbackInfo<void>& info)
{
    TestObjectPython* imp = V8TestObjectPython::toNative(info.Holder());
    V8TRYCATCH_VOID(ScriptPromise, cppValue, ScriptPromise(jsValue, info.GetIsolate()));
    imp->setPromiseAttribute(cppValue);
}
