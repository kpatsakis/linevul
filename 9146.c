void RenderFrameImpl::ReportLegacyTLSVersion(const blink::WebURL& url) {
  url::Origin origin = url::Origin::Create(GURL(url));
  if (base::ContainsKey(tls_version_warning_origins_, origin))
    return;

  size_t num_warnings = tls_version_warning_origins_.size();
  if (num_warnings > kMaxSecurityWarningMessages)
    return;

  if (GetContentClient()
          ->renderer()
          ->SuppressLegacyTLSVersionConsoleMessage()) {
    return;
  }

  std::string console_message;
  if (num_warnings == kMaxSecurityWarningMessages) {
    console_message =
        "Additional resources on this page were loaded with TLS 1.0 or TLS "
        "1.1, which are deprecated and will be disabled in the future. Once "
        "disabled, users will be prevented from loading these resources. "
        "Servers should enable TLS 1.2 or later. See "
        "https://www.chromestatus.com/feature/5654791610957824 for more "
        "information.";
  } else {
    console_message = base::StringPrintf(
        "The connection used to load resources from %s used TLS 1.0 or TLS "
        "1.1, which are deprecated and will be disabled in the future. Once "
        "disabled, users will be prevented from loading these resources. The "
        "server should enable TLS 1.2 or later. See "
        "https://www.chromestatus.com/feature/5654791610957824 for more "
        "information.",
        origin.Serialize().c_str());
  }

  tls_version_warning_origins_.insert(origin);
  AddMessageToConsole(frame_->Parent()
                          ? blink::mojom::ConsoleMessageLevel::kVerbose
                          : blink::mojom::ConsoleMessageLevel::kWarning,
                      console_message);
}
