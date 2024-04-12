PositionTemplate<Strategy> DownstreamIgnoringEditingBoundaries(
    PositionTemplate<Strategy> position) {
  PositionTemplate<Strategy> last_position;
  while (!position.IsEquivalent(last_position)) {
    last_position = position;
    position = MostForwardCaretPosition(position, kCanCrossEditingBoundary);
  }
  return position;
}
