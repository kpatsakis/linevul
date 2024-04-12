void PictureLayerImpl::UpdateIdealScales() {
  DCHECK(CanHaveTilings());

  float min_contents_scale = MinimumContentsScale();
  DCHECK_GT(min_contents_scale, 0.f);
  float min_page_scale = layer_tree_impl()->min_page_scale_factor();
  DCHECK_GT(min_page_scale, 0.f);
  float min_device_scale = 1.f;
  float min_source_scale =
      min_contents_scale / min_page_scale / min_device_scale;

  float ideal_page_scale = draw_properties().page_scale_factor;
  float ideal_device_scale = draw_properties().device_scale_factor;
  float ideal_source_scale = draw_properties().ideal_contents_scale /
                             ideal_page_scale / ideal_device_scale;
  ideal_contents_scale_ =
      std::max(draw_properties().ideal_contents_scale, min_contents_scale);
  ideal_page_scale_ = draw_properties().page_scale_factor;
  ideal_device_scale_ = draw_properties().device_scale_factor;
  ideal_source_scale_ = std::max(ideal_source_scale, min_source_scale);
}
