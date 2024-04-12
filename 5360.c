String UrlForFrame(LocalFrame* frame) {
  KURL url = frame->GetDocument()->Url();
  url.RemoveFragmentIdentifier();
  return url.GetString();
}
