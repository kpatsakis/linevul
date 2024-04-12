static String ValueFontName(const EditorInternalCommand&,
                            LocalFrame& frame,
                            Event*) {
  return ValueStyle(frame, CSSPropertyFontFamily);
}
