HeadlessDevToolsTarget* HeadlessWebContentsImpl::GetDevToolsTarget() {
  return web_contents()->GetMainFrame()->IsRenderFrameLive() ? this : nullptr;
}
