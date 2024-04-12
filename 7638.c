MimeHandlerViewContainer::FromRenderFrame(content::RenderFrame* render_frame) {
  auto it = g_mime_handler_view_container_map.Get().find(render_frame);
  if (it == g_mime_handler_view_container_map.Get().end())
    return std::vector<MimeHandlerViewContainer*>();

  return std::vector<MimeHandlerViewContainer*>(it->second.begin(),
                                                it->second.end());
}
