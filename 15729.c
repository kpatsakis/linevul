CustomElementRegistry* LocalDOMWindow::customElements(
    ScriptState* script_state) const {
  if (!script_state->World().IsMainWorld())
    return nullptr;
  return customElements();
}
