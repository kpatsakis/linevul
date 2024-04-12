void RenderView::didChangeIcon(WebFrame* frame, WebIconURL::Type type) {
  FOR_EACH_OBSERVER(RenderViewObserver, observers_,
                    DidChangeIcon(frame, type));
}
