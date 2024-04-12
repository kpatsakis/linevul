void LaunchUrlWithoutSecurityCheckWithDelegate(
    const GURL& url,
    int render_process_host_id,
    int render_view_routing_id,
    ExternalProtocolHandler::Delegate* delegate) {
  content::WebContents* web_contents = tab_util::GetWebContentsByID(
      render_process_host_id, render_view_routing_id);
  if (delegate) {
    delegate->LaunchUrlWithoutSecurityCheck(url, web_contents);
    return;
  }
  ExternalProtocolHandler::LaunchUrlWithoutSecurityCheck(url, web_contents);
}
