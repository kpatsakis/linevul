static String ValueFontSizeDelta(const EditorInternalCommand&,
                                 LocalFrame& frame,
                                 Event*) {
  return ValueStyle(frame, CSSPropertyWebkitFontSizeDelta);
}
