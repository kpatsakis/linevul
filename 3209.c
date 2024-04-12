void RenderFrameImpl::DidAccessInitialDocument() {
  DCHECK(!frame_->Parent());

  if (!has_accessed_initial_document_) {
    NavigationState* navigation_state =
        NavigationState::FromDocumentLoader(frame_->GetDocumentLoader());
    if (!navigation_state->request_committed()) {
      Send(new FrameHostMsg_DidAccessInitialDocument(routing_id_));
    }
  }

  has_accessed_initial_document_ = true;
}
