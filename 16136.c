const AtomicString& TextTrack::CaptionsKeyword() {
  DEFINE_STATIC_LOCAL(const AtomicString, captions, ("captions"));
  return captions;
}
