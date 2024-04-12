void ImeObserver::OnReset(const std::string& component_id) {
  if (extension_id_.empty() || !HasListener(input_ime::OnReset::kEventName))
    return;

  std::unique_ptr<base::ListValue> args(
      input_ime::OnReset::Create(component_id));

  DispatchEventToExtension(extensions::events::INPUT_IME_ON_RESET,
                           input_ime::OnReset::kEventName, std::move(args));
}
