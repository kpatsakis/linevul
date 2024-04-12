void ChromeClientImpl::ClearCompositedSelection(LocalFrame* frame) {
  LocalFrame& local_root = frame->LocalFrameRoot();
  WebFrameWidgetBase* widget =
      WebLocalFrameImpl::FromFrame(&local_root)->FrameWidget();
  WebWidgetClient* client = widget->Client();
  if (!client)
    return;

  if (WebLayerTreeView* layer_tree_view = widget->GetLayerTreeView())
    layer_tree_view->ClearSelection();
}
