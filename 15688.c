bool RenderFrameImpl::ShouldDisplayErrorPageForFailedLoad(
    int error_code,
    const GURL& unreachable_url) {
  if (error_code == net::ERR_ABORTED)
    return false;

  if (error_code == net::ERR_BLOCKED_BY_CLIENT &&
      render_view_->renderer_preferences_.disable_client_blocked_error_page) {
    return false;
  }

  if (GetContentClient()->renderer()->ShouldSuppressErrorPage(
          this, unreachable_url)) {
    return false;
  }

  if (RenderThreadImpl::current() &&
      RenderThreadImpl::current()->layout_test_mode()) {
    return false;
  }

  return true;
}
