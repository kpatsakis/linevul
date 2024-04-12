static bool EnabledUndo(LocalFrame& frame, Event*, EditorCommandSource) {
  return frame.GetEditor().CanUndo();
}
