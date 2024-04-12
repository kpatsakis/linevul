WebContents* FindFirstDevToolsContents() {
  std::unique_ptr<content::RenderWidgetHostIterator> widgets(
      RenderWidgetHost::GetRenderWidgetHosts());
  while (content::RenderWidgetHost* widget = widgets->GetNextHost()) {
    if (!widget->GetProcess()->IsInitializedAndNotDead())
      continue;
    RenderViewHost* view_host = RenderViewHost::From(widget);
    if (!view_host)
      continue;
    WebContents* contents = WebContents::FromRenderViewHost(view_host);
    GURL url = contents->GetURL();
    if (url.SchemeIs(content::kChromeDevToolsScheme))
      return contents;
  }
  return NULL;
}
