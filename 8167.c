static void conditionalMethod2Method(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TestObject* imp = V8TestObject::toNative(info.Holder());
    imp->conditionalMethod2();
}
