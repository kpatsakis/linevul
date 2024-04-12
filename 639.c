Document& SelectionEditor::GetDocument() const {
  DCHECK(LifecycleContext());
  return *LifecycleContext();
}
