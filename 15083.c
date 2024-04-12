void FrameSelection::SetSelectionFromNone() {

  Document* document = frame_->GetDocument();
  if (!ComputeVisibleSelectionInDOMTreeDeprecated().IsNone() ||
      !(blink::HasEditableStyle(*document)))
    return;

  Element* document_element = document->documentElement();
  if (!document_element)
    return;
  if (HTMLBodyElement* body =
          Traversal<HTMLBodyElement>::FirstChild(*document_element)) {
    SetSelection(SelectionInDOMTree::Builder()
                     .Collapse(FirstPositionInOrBeforeNode(body))
                     .Build());
  }
}
