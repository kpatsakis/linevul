void RenderFrameImpl::DidAccessInitialDocument() {
  DCHECK(!frame_->Parent());

  if (!has_accessed_initial_document_) {
    DocumentState* document_state =
        DocumentState::FromDocumentLoader(frame_->GetDocumentLoader());
    NavigationStateImpl* navigation_state =
        static_cast<NavigationStateImpl*>(document_state->navigation_state());

    if (!navigation_state->request_committed()) {
      Send(new FrameHostMsg_DidAccessInitialDocument(routing_id_));
    }
  }

  has_accessed_initial_document_ = true;
}
