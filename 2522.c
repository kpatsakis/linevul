Range* Document::caretRangeFromPoint(int x, int y) {
  if (GetLayoutViewItem().IsNull())
    return nullptr;

  HitTestResult result = HitTestInDocument(this, x, y);
  PositionWithAffinity position_with_affinity = result.GetPosition();
  if (position_with_affinity.IsNull())
    return nullptr;

  Position range_compliant_position =
      position_with_affinity.GetPosition().ParentAnchoredEquivalent();
  return Range::CreateAdjustedToTreeScope(*this, range_compliant_position);
}
