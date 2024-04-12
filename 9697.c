static void testInterfaceEmptyAttributeAttributeSetter(v8::Local<v8::Value> jsValue, const v8::PropertyCallbackInfo<void>& info)
{
    TestObjectPython* imp = V8TestObjectPython::toNative(info.Holder());
    V8TRYCATCH_VOID(TestInterfaceEmpty*, cppValue, V8TestInterfaceEmpty::toNativeWithTypeCheck(info.GetIsolate(), jsValue));
    imp->setTestInterfaceEmptyAttribute(WTF::getPtr(cppValue));
}
