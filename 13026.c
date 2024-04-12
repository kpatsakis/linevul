void DistillerNativeJavaScript::BindFunctionToObject(
    v8::Local<v8::Object> javascript_object,
    const std::string& name,
    const base::Callback<Sig> callback) {
  v8::Isolate* isolate = javascript_object->GetIsolate();
  javascript_object->Set(
      gin::StringToSymbol(isolate, name),
      gin::CreateFunctionTemplate(isolate, callback)->GetFunction());
 }
