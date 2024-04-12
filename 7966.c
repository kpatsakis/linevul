void LayerTreeHost::SetLayerTreeMutator(
    std::unique_ptr<LayerTreeMutator> mutator) {
  proxy_->SetMutator(std::move(mutator));
}
