void TextTrackCueList::Trace(blink::Visitor* visitor) {
  visitor->Trace(list_);
  ScriptWrappable::Trace(visitor);
}
