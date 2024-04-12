void SafeBrowsingPrivateEventRouter::OnSecurityInterstitialShown(
    const GURL& url,
    const std::string& reason,
    int net_error_code) {
  api::safe_browsing_private::InterstitialInfo params;
  params.url = url.spec();
  params.reason = reason;
  if (net_error_code < 0) {
    params.net_error_code =
        std::make_unique<std::string>(base::NumberToString(net_error_code));
  }
  params.user_name = GetProfileUserName();

  if (event_router_) {
    auto event_value = std::make_unique<base::ListValue>();
    event_value->Append(params.ToValue());

    auto extension_event = std::make_unique<Event>(
        events::SAFE_BROWSING_PRIVATE_ON_SECURITY_INTERSTITIAL_SHOWN,
        api::safe_browsing_private::OnSecurityInterstitialShown::kEventName,
        std::move(event_value));
    event_router_->BroadcastEvent(std::move(extension_event));
  }

  if (client_) {
    base::Value event(base::Value::Type::DICTIONARY);
    event.SetStringKey(kKeyUrl, params.url);
    event.SetStringKey(kKeyReason, params.reason);
    event.SetIntKey(kKeyNetErrorCode, net_error_code);
    event.SetStringKey(kKeyProfileUserName, params.user_name);
    event.SetBoolKey(kKeyClickedThrough, false);
    ReportRealtimeEvent(kKeyInterstitialEvent, std::move(event));
  }
}
