void RenderFrameHostImpl::CreateWebUsbService(
    blink::mojom::WebUsbServiceRequest request) {
  GetContentClient()->browser()->CreateWebUsbService(this, std::move(request));
}
