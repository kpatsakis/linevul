static void perWorldAttributeAttributeGetterForMainWorld(const v8::PropertyCallbackInfo<v8::Value>& info)
{
    TestObject* imp = V8TestObject::toNative(info.Holder());
    v8SetReturnValueForMainWorld(info, WTF::getPtr(imp->perWorldAttribute()));
}
