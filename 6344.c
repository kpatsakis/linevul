void AXNodeObject::setSequentialFocusNavigationStartingPoint() {
  if (!getNode())
    return;

  getNode()->document().clearFocusedElement();
  getNode()->document().setSequentialFocusNavigationStartingPoint(getNode());
}
