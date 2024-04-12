static void unsignedShortAttributeAttributeGetter(const v8::PropertyCallbackInfo<v8::Value>& info)
{
    TestObjectPython* imp = V8TestObjectPython::toNative(info.Holder());
    v8SetReturnValueUnsigned(info, imp->unsignedShortAttribute());
}
