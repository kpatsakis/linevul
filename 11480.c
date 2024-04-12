int WebLocalFrameImpl::SelectNearestFindMatch(const WebFloatPoint& point,
                                              WebRect* selection_rect) {
  return EnsureTextFinder().SelectNearestFindMatch(point, selection_rect);
}
