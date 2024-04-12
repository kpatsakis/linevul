void V8ContextNativeHandler::GetAvailability(
    const v8::FunctionCallbackInfo<v8::Value>& args) {
  CHECK_EQ(args.Length(), 1);
  v8::Isolate* isolate = args.GetIsolate();
  std::string api_name = *v8::String::Utf8Value(args[0]);
  Feature::Availability availability = context_->GetAvailability(api_name);

  v8::Local<v8::Object> ret = v8::Object::New(isolate);
  ret->Set(v8::String::NewFromUtf8(isolate, "is_available"),
           v8::Boolean::New(isolate, availability.is_available()));
  ret->Set(v8::String::NewFromUtf8(isolate, "message"),
           v8::String::NewFromUtf8(isolate, availability.message().c_str()));
  ret->Set(v8::String::NewFromUtf8(isolate, "result"),
           v8::Integer::New(isolate, availability.result()));
  args.GetReturnValue().Set(ret);
}
