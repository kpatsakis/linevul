void RenderViewImpl::OnFindMatchRects(int current_version) {
  if (!webview())
      return;

  WebFrame* main_frame = webview()->mainFrame();
  std::vector<gfx::RectF> match_rects;

  int rects_version = main_frame->findMatchMarkersVersion();
  if (current_version != rects_version) {
    WebVector<WebFloatRect> web_match_rects;
    main_frame->findMatchRects(web_match_rects);
    match_rects.reserve(web_match_rects.size());
    for (size_t i = 0; i < web_match_rects.size(); ++i)
      match_rects.push_back(gfx::RectF(web_match_rects[i]));
  }

  gfx::RectF active_rect = main_frame->activeFindMatchRect();
  Send(new ViewHostMsg_FindMatchRects_Reply(routing_id_,
                                               rects_version,
                                               match_rects,
                                               active_rect));
}
