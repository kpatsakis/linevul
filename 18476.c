static void enabledAtRuntimeAttr2AttrSetter(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::AccessorInfo& info)
{
    INC_STATS("DOM.TestObj.enabledAtRuntimeAttr2._set");
    TestObj* imp = V8TestObj::toNative(info.Holder());
    int v = toInt32(value);
    imp->setEnabledAtRuntimeAttr2(v);
    return;
}
