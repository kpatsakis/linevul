void V8TestObject::NamedPropertyDeleterCallback(
    v8::Local<v8::Name> name, const v8::PropertyCallbackInfo<v8::Boolean>& info) {
  if (!name->IsString())
    return;
  const AtomicString& property_name = ToCoreAtomicString(name.As<v8::String>());

  test_object_v8_internal::NamedPropertyDeleter(property_name, info);
}
