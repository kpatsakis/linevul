bool RenderFrameImpl::ShouldReportDetailedMessageForSource(
    const blink::WebString& source) {
  return GetContentClient()->renderer()->ShouldReportDetailedMessageForSource(
      source.Utf16());
}
