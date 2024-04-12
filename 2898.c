NGConstraintSpace NGColumnLayoutAlgorithm::CreateConstraintSpaceForBalancing(
    const LogicalSize& column_size) const {
  NGConstraintSpaceBuilder space_builder(
      ConstraintSpace(), Style().GetWritingMode(), /* is_new_fc */ true);
  space_builder.SetAvailableSize({column_size.inline_size, kIndefiniteSize});
  space_builder.SetPercentageResolutionSize(column_size);
  space_builder.SetIsAnonymous(true);
  space_builder.SetIsIntermediateLayout(true);

  return space_builder.ToConstraintSpace();
}
