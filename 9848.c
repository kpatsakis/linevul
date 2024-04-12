void RenderViewImpl::UpdateTitle(WebFrame* frame,
                                 const string16& title,
                                 WebTextDirection title_direction) {
  if (frame->parent())
    return;

  string16 shortened_title = title.substr(0, content::kMaxTitleChars);
  Send(new ViewHostMsg_UpdateTitle(routing_id_, page_id_, shortened_title,
                                   title_direction));
}
