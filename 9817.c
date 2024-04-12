bool WebLocalFrameImpl::HasVisibleContent() const {
  LayoutEmbeddedContentItem layout_item = GetFrame()->OwnerLayoutItem();
  if (!layout_item.IsNull() &&
      layout_item.Style()->Visibility() != EVisibility::kVisible) {
    return false;
  }

  if (LocalFrameView* view = GetFrameView())
    return view->VisibleWidth() > 0 && view->VisibleHeight() > 0;
  return false;
}
