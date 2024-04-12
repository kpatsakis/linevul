static v8::Local<v8::Value> installPrivateScriptRunner(v8::Isolate* isolate) {
  const String className = "PrivateScriptRunner";
  size_t index;
  for (index = 0; index < WTF_ARRAY_LENGTH(kPrivateScriptSources); index++) {
    if (className == kPrivateScriptSources[index].className)
      break;
  }
  if (index == WTF_ARRAY_LENGTH(kPrivateScriptSources)) {
    LOG(FATAL)
        << "Private script error: Target source code was not found. (Class "
           "name = "
        << className.utf8().data() << ")";
  }
  String resourceData =
      loadResourceAsASCIIString(kPrivateScriptSources[index].resourceFile);
  return compileAndRunPrivateScript(ScriptState::current(isolate), className,
                                    resourceData.utf8().data(),
                                    resourceData.length());
}
