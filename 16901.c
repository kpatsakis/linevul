void AXLayoutObject::setSelection(const AXRange& selection) {
  if (!getLayoutObject() || !selection.isValid())
    return;

  AXObject* anchorObject =
      selection.anchorObject ? selection.anchorObject.get() : this;
  AXObject* focusObject =
      selection.focusObject ? selection.focusObject.get() : this;

  if (!isValidSelectionBound(anchorObject) ||
      !isValidSelectionBound(focusObject)) {
    return;
  }

  if (anchorObject == focusObject &&
      anchorObject->getLayoutObject()->isTextControl()) {
    TextControlElement* textControl =
        toLayoutTextControl(anchorObject->getLayoutObject())
            ->textControlElement();
    if (selection.anchorOffset <= selection.focusOffset) {
      textControl->setSelectionRange(selection.anchorOffset,
                                     selection.focusOffset,
                                     SelectionHasForwardDirection);
    } else {
      textControl->setSelectionRange(selection.focusOffset,
                                     selection.anchorOffset,
                                     SelectionHasBackwardDirection);
    }
    return;
  }

  LocalFrame* frame = getLayoutObject()->frame();
  if (!frame)
    return;

  frame->document()->updateStyleAndLayoutIgnorePendingStylesheets();

  VisiblePosition anchorVisiblePosition =
      toVisiblePosition(anchorObject, selection.anchorOffset);
  VisiblePosition focusVisiblePosition =
      toVisiblePosition(focusObject, selection.focusOffset);
  if (anchorVisiblePosition.isNull() || focusVisiblePosition.isNull())
    return;

  frame->selection().setSelection(
      SelectionInDOMTree::Builder()
          .collapse(anchorVisiblePosition.toPositionWithAffinity())
          .extend(focusVisiblePosition.deepEquivalent())
          .build());
}
