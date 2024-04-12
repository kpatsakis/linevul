void LayerTreeHost::SetRootLayer(scoped_refptr<Layer> root_layer) {
  if (root_layer_.get() == root_layer.get())
    return;

  if (root_layer_.get())
    root_layer_->SetLayerTreeHost(nullptr);
  root_layer_ = root_layer;
  if (root_layer_.get()) {
    DCHECK(!root_layer_->parent());
    root_layer_->SetLayerTreeHost(this);
  }

  if (hud_layer_.get())
    hud_layer_->RemoveFromParent();

  ResetGpuRasterizationTracking();

  SetNeedsFullTreeSync();
}
