static bool AcceptsEditingFocus(const Element& element) {
  DCHECK(HasEditableStyle(element));

  return element.GetDocument().GetFrame() && RootEditableElement(element);
}
