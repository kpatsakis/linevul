static WeakDocumentSet& liveDocumentSet() {
  DEFINE_STATIC_LOCAL(blink::Persistent<WeakDocumentSet>, set,
                      (blink::MakeGarbageCollected<WeakDocumentSet>()));
  return *set;
}
