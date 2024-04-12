std::unique_ptr<WebUIImpl> WebContentsImpl::CreateWebUIForRenderFrameHost(
    const GURL& url) {
  return CreateWebUI(url, std::string());
}
