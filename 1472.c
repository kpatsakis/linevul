static String ValueDefaultParagraphSeparator(const EditorInternalCommand&,
                                             LocalFrame& frame,
                                             Event*) {
  switch (frame.GetEditor().DefaultParagraphSeparator()) {
    case kEditorParagraphSeparatorIsDiv:
      return divTag.LocalName();
    case kEditorParagraphSeparatorIsP:
      return pTag.LocalName();
  }

  NOTREACHED();
  return String();
}
