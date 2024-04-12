bool Document::IsSlotAssignmentOrLegacyDistributionDirty() {
  if (ChildNeedsDistributionRecalc())
    return true;
  if (RuntimeEnabledFeatures::IncrementalShadowDOMEnabled() &&
      GetSlotAssignmentEngine().HasPendingSlotAssignmentRecalc()) {
    return true;
  }
  return false;
}
