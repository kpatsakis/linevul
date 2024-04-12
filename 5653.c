void RenderViewTest::Reload(const GURL& url) {
  ViewMsg_Navigate_Params params;
  params.url = url;
  params.navigation_type = ViewMsg_Navigate_Type::RELOAD;
  RenderViewImpl* impl = static_cast<RenderViewImpl*>(view_);
  impl->OnNavigate(params);
}
