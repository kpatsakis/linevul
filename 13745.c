InputEngineContext::InputEngineContext(const std::string& ime) : ime_spec(ime) {
  std::string id = GetIdFromImeSpec(ime_spec);
  if (rulebased::Engine::IsImeSupported(id)) {
    engine = std::make_unique<rulebased::Engine>();
    engine->Activate(id);
  }
}
