static void TestDictionaryMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestObject* impl = V8TestObject::ToImpl(info.Holder());

  TestDictionary* result = impl->testDictionaryMethod();
  V8SetReturnValue(info, result);
}
