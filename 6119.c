  RendererURLRequestContextSelector(BrowserContext* browser_context,
                                    int render_child_id)
      : request_context_(browser_context->GetRequestContextForRenderProcess(
                             render_child_id)),
        media_request_context_(
            browser_context->GetMediaRequestContextForRenderProcess(
                render_child_id)) {
  }
