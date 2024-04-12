v8::Local<v8::Value> ModuleSystem::CallModuleMethod(
    const std::string& module_name,
    const std::string& method_name,
    std::vector<v8::Local<v8::Value>>* args) {
  return CallModuleMethod(module_name, method_name, args->size(), args->data());
}
