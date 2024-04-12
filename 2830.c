static bool EnabledInRichlyEditableText(LocalFrame& frame,
                                        Event*,
                                        EditorCommandSource source) {
  frame.GetDocument()->UpdateStyleAndLayoutIgnorePendingStylesheets();
  if (source == kCommandFromMenuOrKeyBinding &&
      !frame.Selection().SelectionHasFocus())
    return false;
  return !frame.Selection()
              .ComputeVisibleSelectionInDOMTreeDeprecated()
              .IsNone() &&
         frame.Selection()
             .ComputeVisibleSelectionInDOMTreeDeprecated()
             .IsContentRichlyEditable() &&
         frame.Selection()
             .ComputeVisibleSelectionInDOMTreeDeprecated()
             .RootEditableElement();
}
