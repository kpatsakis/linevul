static bool ExecuteInsertLineBreak(LocalFrame& frame,
                                   Event* event,
                                   EditorCommandSource source,
                                   const String&) {
  switch (source) {
    case kCommandFromMenuOrKeyBinding:
      return TargetFrame(frame, event)
          ->GetEventHandler()
          .HandleTextInputEvent("\n", event, kTextEventInputLineBreak);
    case kCommandFromDOM:
      DCHECK(frame.GetDocument());
      return TypingCommand::InsertLineBreak(*frame.GetDocument());
  }
  NOTREACHED();
  return false;
}
