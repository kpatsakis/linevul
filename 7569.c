WebLocalFrameImpl* WebLocalFrameImpl::CreateMainFrame(
    WebView* web_view,
    WebFrameClient* client,
    InterfaceRegistry* interface_registry,
    WebFrame* opener,
    const WebString& name,
    WebSandboxFlags sandbox_flags) {
  WebLocalFrameImpl* frame = new WebLocalFrameImpl(WebTreeScopeType::kDocument,
                                                   client, interface_registry);
  frame->SetOpener(opener);
  Page& page = *static_cast<WebViewBase*>(web_view)->GetPage();
  DCHECK(!page.MainFrame());
  frame->InitializeCoreFrame(page, nullptr, name);
  frame->GetFrame()->Loader().ForceSandboxFlags(
      static_cast<SandboxFlags>(sandbox_flags));
  return frame;
}
