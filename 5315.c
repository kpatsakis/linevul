void RemoteFrame::Navigate(Document& origin_document,
                           const KURL& url,
                           bool replace_current_item,
                           UserGestureStatus user_gesture_status) {
  FrameLoadRequest frame_request(&origin_document, ResourceRequest(url));
  frame_request.SetReplacesCurrentItem(replace_current_item);
  frame_request.GetResourceRequest().SetHasUserGesture(
      user_gesture_status == UserGestureStatus::kActive);
  frame_request.GetResourceRequest().SetFrameType(
      IsMainFrame() ? network::mojom::RequestContextFrameType::kTopLevel
                    : network::mojom::RequestContextFrameType::kNested);
  Navigate(frame_request);
}
