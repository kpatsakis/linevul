void RenderFrameImpl::MaybeSetDownloadFramePolicy(
    bool is_opener_navigation,
    const blink::WebURLRequest& request,
    const blink::WebSecurityOrigin& current_origin,
    bool has_download_sandbox_flag,
    bool blocking_downloads_in_sandbox_without_user_activation_enabled,
    bool from_ad,
    NavigationDownloadPolicy* download_policy) {
  if (is_opener_navigation &&
      !request.RequestorOrigin().CanAccess(current_origin)) {
    download_policy->SetDisallowed(NavigationDownloadType::kOpenerCrossOrigin);
  }
  if (has_download_sandbox_flag && !request.HasUserGesture()) {
    if (blocking_downloads_in_sandbox_without_user_activation_enabled) {
      download_policy->SetDisallowed(NavigationDownloadType::kSandboxNoGesture);
    } else {
      download_policy->SetAllowed(NavigationDownloadType::kSandboxNoGesture);
    }
  }
  if (from_ad) {
    if (!request.HasUserGesture()) {
      if (base::FeatureList::IsEnabled(
              blink::features::
                  kBlockingDownloadsInAdFrameWithoutUserActivation)) {
        download_policy->SetDisallowed(
            NavigationDownloadType::kAdFrameNoGesture);
      } else {
        download_policy->SetAllowed(NavigationDownloadType::kAdFrameNoGesture);
      }
    } else {
      download_policy->SetAllowed(NavigationDownloadType::kAdFrameGesture);
    }
  }
}
