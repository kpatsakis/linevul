static void XMLObjAttrAttributeSetter(v8::Local<v8::Value> jsValue, const v8::PropertyCallbackInfo<void>& info)
{
    TestObject* imp = V8TestObject::toNative(info.Holder());
    V8TRYCATCH_VOID(TestObject*, cppValue, V8TestObject::toNativeWithTypeCheck(info.GetIsolate(), jsValue));
    imp->setXMLObjAttr(WTF::getPtr(cppValue));
}
