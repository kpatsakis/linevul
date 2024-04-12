void Document::Initialize() {
  DCHECK_EQ(lifecycle_.GetState(), DocumentLifecycle::kInactive);
  DCHECK(!ax_object_cache_ || this != &AxObjectCacheOwner());

  layout_view_ = new LayoutView(this);
  SetLayoutObject(layout_view_);

  layout_view_->SetIsInWindow(true);
  layout_view_->SetStyle(StyleResolver::StyleForViewport(*this));
  layout_view_->Compositor()->SetNeedsCompositingUpdate(
      kCompositingUpdateAfterCompositingInputChange);

  AttachContext context;
  ContainerNode::AttachLayoutTree(context);

  if (TextAutosizer* autosizer = GetTextAutosizer())
    autosizer->UpdatePageInfo();

  frame_->DocumentAttached();
  lifecycle_.AdvanceTo(DocumentLifecycle::kStyleClean);

  if (View())
    View()->DidAttachDocument();

  network_state_observer_ = new NetworkStateObserver(*this);
}
