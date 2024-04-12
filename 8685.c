void SaveImpl(const char* name,
              v8::Local<v8::Value> value,
              v8::Local<v8::Context> context) {
  CHECK(!value.IsEmpty() && value->IsObject()) << name;
  context->Global()
      ->SetPrivate(context, MakeKey(name, context->GetIsolate()), value)
      .FromJust();
}
