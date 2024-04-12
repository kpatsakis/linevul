void PaintLayerScrollableArea::InvalidateStickyConstraintsFor(
    PaintLayer* layer,
    bool needs_compositing_update) {
  if (PaintLayerScrollableAreaRareData* d = RareData()) {
    d->sticky_constraints_map_.erase(layer);
    if (needs_compositing_update &&
        layer->GetLayoutObject().StyleRef().HasStickyConstrainedPosition()) {
      layer->SetNeedsCompositingInputsUpdate();
      layer->GetLayoutObject().SetNeedsPaintPropertyUpdate();
    }
  }
}
