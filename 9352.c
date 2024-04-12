  void ClearStates() {
    STLDeleteContainerPointers(states_.begin(), states_.end());
    states_.clear();
  }
