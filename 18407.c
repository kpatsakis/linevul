RenderFrameHost* ConvertToRenderFrameHost(WebContents* web_contents) {
  return web_contents->GetMainFrame();
}
