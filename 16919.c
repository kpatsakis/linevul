bool LayerTreeHostImpl::AnimationsPreserveAxisAlignment(
    const LayerImpl* layer) const {
  return mutator_host_->AnimationsPreserveAxisAlignment(layer->element_id());
}
