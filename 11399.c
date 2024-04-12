void ChromeContentBrowserClient::CreateMediaRemoter(
    content::RenderFrameHost* render_frame_host,
    media::mojom::RemotingSourcePtr source,
    media::mojom::RemoterRequest request) {
  CastRemotingConnector::CreateMediaRemoter(
      render_frame_host, std::move(source), std::move(request));
}
