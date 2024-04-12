bool ObjectBackedNativeHandler::GetPrivate(v8::Local<v8::Object> obj,
                                           const char* key,
                                           v8::Local<v8::Value>* result) {
  return GetPrivate(context_->v8_context(), obj, key, result);
}
