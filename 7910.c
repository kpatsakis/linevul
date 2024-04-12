void BaseRenderingContext2D::setLineDash(const Vector<double>& dash) {
  if (!LineDashSequenceIsValid(dash))
    return;
  ModifiableState().SetLineDash(dash);
}
