bool FrameFetchContext::PageDismissalEventBeingDispatched() const {
  return document_ && document_->PageDismissalEventBeingDispatched() !=
                          Document::kNoDismissal;
}
