void RenderFrameImpl::SendUpdateFaviconURL() {
  if (frame_->Parent())
    return;

  blink::WebIconURL::Type icon_types_mask =
      static_cast<blink::WebIconURL::Type>(
          blink::WebIconURL::kTypeFavicon |
          blink::WebIconURL::kTypeTouchPrecomposed |
          blink::WebIconURL::kTypeTouch);

  WebVector<blink::WebIconURL> icon_urls = frame_->IconURLs(icon_types_mask);
  if (icon_urls.empty())
    return;

  std::vector<FaviconURL> urls;
  urls.reserve(icon_urls.size());
  for (const blink::WebIconURL& icon_url : icon_urls) {
    urls.push_back(FaviconURL(icon_url.GetIconURL(),
                              ToFaviconType(icon_url.IconType()),
                              ConvertToFaviconSizes(icon_url.Sizes())));
  }
  DCHECK_EQ(icon_urls.size(), urls.size());

  Send(new FrameHostMsg_UpdateFaviconURL(GetRoutingID(), urls));
}
