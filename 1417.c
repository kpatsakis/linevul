static Range* FindStringBetweenPositions(
    const String& target,
    const EphemeralRangeTemplate<Strategy>& reference_range,
    FindOptions options) {
  EphemeralRangeTemplate<Strategy> search_range(reference_range);

  bool forward = !(options & kBackwards);

  while (true) {
    EphemeralRangeTemplate<Strategy> result_range =
        FindPlainText(search_range, target, options);
    if (result_range.IsCollapsed())
      return nullptr;

    Range* range_object =
        Range::Create(result_range.GetDocument(),
                      ToPositionInDOMTree(result_range.StartPosition()),
                      ToPositionInDOMTree(result_range.EndPosition()));
    if (!range_object->collapsed())
      return range_object;

    if (forward) {
      search_range = EphemeralRangeTemplate<Strategy>(
          NextPositionOf(result_range.StartPosition(),
                         PositionMoveType::kGraphemeCluster),
          search_range.EndPosition());
    } else {
      search_range = EphemeralRangeTemplate<Strategy>(
          search_range.StartPosition(),
          PreviousPositionOf(result_range.EndPosition(),
                             PositionMoveType::kGraphemeCluster));
    }
  }

  NOTREACHED();
  return nullptr;
}
