void RenderFrameHostImpl::BindPresentationServiceRequest(
    blink::mojom::PresentationServiceRequest request) {
  if (!presentation_service_)
    presentation_service_ = PresentationServiceImpl::Create(this);

  presentation_service_->Bind(std::move(request));
}
