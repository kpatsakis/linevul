FloatClipRect GeometryMapper::LocalToAncestorClipRect(
    const PropertyTreeState& local_state,
    const PropertyTreeState& ancestor_state,
    OverlayScrollbarClipBehavior clip_behavior) {
  if (local_state.Clip() == ancestor_state.Clip())
    return FloatClipRect();

  bool success = false;
  auto result = LocalToAncestorClipRectInternal(
      local_state.Clip(), ancestor_state.Clip(), ancestor_state.Transform(),
      clip_behavior, kNonInclusiveIntersect, success);
  DCHECK(success);

  if (local_state.Effect() != ancestor_state.Effect())
    result.ClearIsTight();

  return result;
}
