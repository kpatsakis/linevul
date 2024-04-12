void RenderFrameImpl::DidFailLoad(const WebURLError& error,
                                  blink::WebHistoryCommitType commit_type) {
  TRACE_EVENT1("navigation,rail", "RenderFrameImpl::didFailLoad",
               "id", routing_id_);
  WebDocumentLoader* document_loader = frame_->GetDocumentLoader();
  DCHECK(document_loader);

  const WebURLRequest& failed_request = document_loader->GetRequest();
  base::string16 error_description;
  GetContentClient()->renderer()->PrepareErrorPage(this, failed_request, error,
                                                   nullptr, &error_description);
  Send(new FrameHostMsg_DidFailLoadWithError(
      routing_id_, failed_request.Url(), error.reason(), error_description));
}
