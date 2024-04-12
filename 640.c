  void RemoveAncestorObservers() {
    for (auto* ancestor : ancestors_)
      ancestor->RemoveObserver(this);
    ancestors_.clear();
  }
