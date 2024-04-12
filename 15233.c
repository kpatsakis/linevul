void PaintLayerScrollableArea::RegisterForAnimation() {
  if (HasBeenDisposed())
    return;
  if (LocalFrame* frame = GetLayoutBox()->GetFrame()) {
    if (LocalFrameView* frame_view = frame->View())
      frame_view->AddAnimatingScrollableArea(this);
  }
}
