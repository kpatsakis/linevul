static void NewObjectTestInterfaceMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info) {
  TestObject* impl = V8TestObject::ToImpl(info.Holder());

  TestInterfaceImplementation* result = impl->newObjectTestInterfaceMethod();
  DCHECK(!result || DOMDataStore::GetWrapper(result, info.GetIsolate()).IsEmpty());
  V8SetReturnValue(info, result);
}
