void RenderFrameImpl::DidDisplayContentWithCertificateErrors() {
  Send(new FrameHostMsg_DidDisplayContentWithCertificateErrors(routing_id_));
}
