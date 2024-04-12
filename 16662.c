bool PaintPropertyTreeBuilder::UpdateForSelf() {
  UpdatePaintingLayer();

  bool property_added_or_removed = false;
  if (ObjectTypeMightNeedPaintProperties())
    property_added_or_removed = UpdateFragments();
  else
    object_.GetMutableForPainting().FirstFragment().ClearNextFragment();

  bool property_changed = false;
  auto* fragment_data = &object_.GetMutableForPainting().FirstFragment();
  for (auto& fragment_context : context_.fragments) {
    FragmentPaintPropertyTreeBuilder builder(object_, context_,
                                             fragment_context, *fragment_data);
    builder.UpdateForSelf();
    property_changed |= builder.PropertyChanged();
    property_added_or_removed |= builder.PropertyAddedOrRemoved();
    fragment_data = fragment_data->NextFragment();
  }
  DCHECK(!fragment_data);

  if (property_added_or_removed &&
      RuntimeEnabledFeatures::SlimmingPaintV175Enabled())
    context_.painting_layer->SetNeedsRepaint();

  return property_changed;
}
