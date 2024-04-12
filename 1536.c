void ModuleSystem::RegisterNativeHandler(
    const std::string& name,
    scoped_ptr<NativeHandler> native_handler) {
  ClobberExistingNativeHandler(name);
  native_handler_map_[name] =
      linked_ptr<NativeHandler>(native_handler.release());
}
