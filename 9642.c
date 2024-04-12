AXObject::AXRange AXLayoutObject::selection() const {
  AXRange textSelection = textControlSelection();
  if (textSelection.isValid())
    return textSelection;

  if (!getLayoutObject() || !getLayoutObject()->frame())
    return AXRange();

  VisibleSelection selection =
      getLayoutObject()
          ->frame()
          ->selection()
          .computeVisibleSelectionInDOMTreeDeprecated();
  if (selection.isNone())
    return AXRange();

  VisiblePosition visibleStart = selection.visibleStart();
  Position start = visibleStart.toParentAnchoredPosition();
  TextAffinity startAffinity = visibleStart.affinity();
  VisiblePosition visibleEnd = selection.visibleEnd();
  Position end = visibleEnd.toParentAnchoredPosition();
  TextAffinity endAffinity = visibleEnd.affinity();

  Node* anchorNode = start.anchorNode();
  ASSERT(anchorNode);

  AXLayoutObject* anchorObject = nullptr;
  while (anchorNode) {
    anchorObject = getUnignoredObjectFromNode(*anchorNode);
    if (anchorObject)
      break;

    if (anchorNode->nextSibling())
      anchorNode = anchorNode->nextSibling();
    else
      anchorNode = anchorNode->parentNode();
  }

  Node* focusNode = end.anchorNode();
  ASSERT(focusNode);

  AXLayoutObject* focusObject = nullptr;
  while (focusNode) {
    focusObject = getUnignoredObjectFromNode(*focusNode);
    if (focusObject)
      break;

    if (focusNode->previousSibling())
      focusNode = focusNode->previousSibling();
    else
      focusNode = focusNode->parentNode();
  }

  if (!anchorObject || !focusObject)
    return AXRange();

  int anchorOffset = anchorObject->indexForVisiblePosition(visibleStart);
  ASSERT(anchorOffset >= 0);
  int focusOffset = focusObject->indexForVisiblePosition(visibleEnd);
  ASSERT(focusOffset >= 0);
  return AXRange(anchorObject, anchorOffset, startAffinity, focusObject,
                 focusOffset, endAffinity);
}
