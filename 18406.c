void WebContentsImpl::GetNFC(device::mojom::NFCRequest request) {
  if (!nfc_host_)
    nfc_host_.reset(new NFCHost(this));
  nfc_host_->GetNFC(std::move(request));
}
