bool WebLocalFrameImpl::SelectWordAroundCaret() {
  TRACE_EVENT0("blink", "WebLocalFrameImpl::selectWordAroundCaret");

  FrameSelection& selection = GetFrame()->Selection();

  GetFrame()->GetDocument()->UpdateStyleAndLayoutIgnorePendingStylesheets();

  if (selection.ComputeVisibleSelectionInDOMTree().IsNone() ||
      selection.ComputeVisibleSelectionInDOMTree().IsRange()) {
    return false;
  }

  return GetFrame()->Selection().SelectWordAroundPosition(
      selection.ComputeVisibleSelectionInDOMTree().VisibleStart());
}
