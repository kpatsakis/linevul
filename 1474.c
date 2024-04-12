void WebBluetoothServiceImpl::RequestScanningStartImpl(
    blink::mojom::WebBluetoothScanClientAssociatedPtr client,
    blink::mojom::WebBluetoothRequestLEScanOptionsPtr options,
    RequestScanningStartCallback callback,
    device::BluetoothAdapter* adapter) {
  DCHECK_CURRENTLY_ON(BrowserThread::UI);

  if (IsRequestScanOptionsInvalid(options)) {
    CrashRendererAndClosePipe(bad_message::BDH_INVALID_OPTIONS);
    return;
  }

  if (!adapter) {
    auto result = blink::mojom::RequestScanningStartResult::NewErrorResult(
        blink::mojom::WebBluetoothResult::BLUETOOTH_LOW_ENERGY_NOT_AVAILABLE);
    std::move(callback).Run(std::move(result));
    return;
  }

  const url::Origin requesting_origin =
      render_frame_host_->GetLastCommittedOrigin();
  const url::Origin embedding_origin =
      web_contents()->GetMainFrame()->GetLastCommittedOrigin();

  bool blocked = GetContentClient()->browser()->IsBluetoothScanningBlocked(
      web_contents()->GetBrowserContext(), requesting_origin, embedding_origin);

  if (blocked) {
    auto result = blink::mojom::RequestScanningStartResult::NewErrorResult(
        blink::mojom::WebBluetoothResult::SCANNING_BLOCKED);
    std::move(callback).Run(std::move(result));
    return;
  }

  if (discovery_callback_) {
    auto result = blink::mojom::RequestScanningStartResult::NewErrorResult(
        blink::mojom::WebBluetoothResult::PROMPT_CANCELED);
    std::move(callback).Run(std::move(result));
    return;
  }

  if (discovery_session_) {
    if (AreScanFiltersAllowed(options->filters)) {
      auto scanning_client = std::make_unique<ScanningClient>(
          std::move(client), std::move(options), std::move(callback), nullptr);
      scanning_client->RunRequestScanningStartCallback(
          blink::mojom::WebBluetoothResult::SUCCESS);
      scanning_client->set_allow_send_event(true);
      scanning_clients_.push_back(std::move(scanning_client));
      return;
    }

    device_scanning_prompt_controller_ =
        std::make_unique<BluetoothDeviceScanningPromptController>(
            this, render_frame_host_);

    scanning_clients_.push_back(std::make_unique<ScanningClient>(
        std::move(client), std::move(options), std::move(callback),
        device_scanning_prompt_controller_.get()));
    device_scanning_prompt_controller_->ShowPermissionPrompt();
    return;
  }

  discovery_callback_ = std::move(callback);

  adapter->StartDiscoverySession(
      base::Bind(&WebBluetoothServiceImpl::OnStartDiscoverySession,
                 weak_ptr_factory_.GetWeakPtr(), base::Passed(&client),
                 base::Passed(&options)),
      base::Bind(&WebBluetoothServiceImpl::OnDiscoverySessionError,
                 weak_ptr_factory_.GetWeakPtr()));
}
