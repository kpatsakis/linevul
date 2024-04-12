static void documentFragmentAttributeAttributeGetter(const v8::PropertyCallbackInfo<v8::Value>& info)
{
    TestObjectPython* imp = V8TestObjectPython::toNative(info.Holder());
    v8SetReturnValueFast(info, WTF::getPtr(imp->documentFragmentAttribute()), imp);
}
