uint64_t PaintLayerScrollableArea::Id() const {
  return DOMNodeIds::IdForNode(GetLayoutBox()->GetNode());
}
