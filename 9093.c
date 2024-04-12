bool Compositor::HasObserver(const CompositorObserver* observer) const {
  return observer_list_.HasObserver(observer);
}
