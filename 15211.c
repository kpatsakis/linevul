scoped_ptr<LayerImpl> PictureLayer::CreateLayerImpl(LayerTreeImpl* tree_impl) {
  return PictureLayerImpl::Create(tree_impl, id(), is_mask_);
}
