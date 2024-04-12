InlineBoxPosition ComputeInlineBoxPosition(const Position& position,
                                           TextAffinity affinity,
                                           TextDirection primary_direction) {
  return ComputeInlineBoxPositionTemplate<EditingStrategy>(position, affinity,
                                                           primary_direction);
}
