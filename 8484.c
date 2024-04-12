void LocalFrameClientImpl::ScrollRectToVisibleInParentFrame(
    const WebRect& rect_to_scroll,
    const WebScrollIntoViewParams& params) {
  web_frame_->Client()->ScrollRectToVisibleInParentFrame(rect_to_scroll,
                                                         params);
}
