void WebLocalFrameImpl::SetCommittedFirstRealLoad() {
  DCHECK(GetFrame());
  EnsureFrameLoaderHasCommitted(GetFrame()->Loader());
}
