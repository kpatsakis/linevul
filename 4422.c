Document& FrameSelection::GetDocument() const {
  DCHECK(LifecycleContext());
  return *LifecycleContext();
}
