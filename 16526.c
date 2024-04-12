void RenderFrameHostImpl::OnSmartClipDataExtracted(uint32_t id,
                                                   base::string16 text,
                                                   base::string16 html) {
  auto it = smart_clip_callbacks_.find(id);
  if (it != smart_clip_callbacks_.end()) {
    it->second.Run(text, html);
    smart_clip_callbacks_.erase(it);
  } else {
    NOTREACHED() << "Received smartclip data response for unknown request";
  }
}
