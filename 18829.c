static void reflectedURLAttrAttributeSetter(v8::Local<v8::Value> jsValue, const v8::PropertyCallbackInfo<void>& info)
{
    TestObject* imp = V8TestObject::toNative(info.Holder());
    V8TRYCATCH_FOR_V8STRINGRESOURCE_VOID(V8StringResource<>, cppValue, jsValue);
    CustomElementCallbackDispatcher::CallbackDeliveryScope deliveryScope;
    imp->setAttribute(HTMLNames::reflectedurlattrAttr, cppValue);
}
