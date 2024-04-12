void ObjectBackedNativeHandler::DeletePrivate(v8::Local<v8::Context> context,
                                              v8::Local<v8::Object> obj,
                                              const char* key) {
  obj->DeletePrivate(context,
                     v8::Private::ForApi(
                         context->GetIsolate(),
                         v8::String::NewFromUtf8(context->GetIsolate(), key)))
      .FromJust();
}
