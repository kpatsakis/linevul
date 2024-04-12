void RenderFrameHostImpl::CreateUsbChooserService(
    device::mojom::UsbChooserServiceRequest request) {
  GetContentClient()->browser()->CreateUsbChooserService(this,
                                                         std::move(request));
}
