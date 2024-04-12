void Layer::SetPositionConstraint(const LayerPositionConstraint& constraint) {
  DCHECK(IsPropertyChangeAllowed());
  if (position_constraint_ == constraint)
    return;
  position_constraint_ = constraint;
  SetNeedsCommit();
}
