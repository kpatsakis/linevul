void PrintNativeHandler::Print(
    const v8::FunctionCallbackInfo<v8::Value>& args) {
  if (args.Length() < 1)
    return;

  std::vector<std::string> components;
  for (int i = 0; i < args.Length(); ++i)
    components.push_back(*v8::String::Utf8Value(args[i]));

  LOG(ERROR) << base::JoinString(components, ",");
}
