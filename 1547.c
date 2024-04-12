void ModuleSystem::SetLazyField(v8::Local<v8::Object> object,
                                const std::string& field,
                                const std::string& module_name,
                                const std::string& module_field) {
  SetLazyField(
      object, field, module_name, module_field, &ModuleSystem::LazyFieldGetter);
}
