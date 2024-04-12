void FrameSelection::SelectFrameElementInParentIfFullySelected() {
  Frame* parent = frame_->Tree().Parent();
  if (!parent)
    return;
  Page* page = frame_->GetPage();
  if (!page)
    return;

  if (GetSelectionInDOMTree().Type() != kRangeSelection) {
    return;
  }

  GetDocument().UpdateStyleAndLayoutIgnorePendingStylesheets();

  if (!IsStartOfDocument(ComputeVisibleSelectionInDOMTree().VisibleStart()))
    return;
  if (!IsEndOfDocument(ComputeVisibleSelectionInDOMTree().VisibleEnd()))
    return;

  if (!parent->IsLocalFrame())
    return;

  HTMLFrameOwnerElement* owner_element = frame_->DeprecatedLocalOwner();
  if (!owner_element)
    return;
  ContainerNode* owner_element_parent = owner_element->parentNode();
  if (!owner_element_parent)
    return;

  owner_element_parent->GetDocument()
      .UpdateStyleAndLayoutIgnorePendingStylesheets();

  if (!blink::HasEditableStyle(*owner_element_parent))
    return;

  unsigned owner_element_node_index = owner_element->NodeIndex();
  VisiblePosition before_owner_element = CreateVisiblePosition(
      Position(owner_element_parent, owner_element_node_index));
  VisiblePosition after_owner_element = CreateVisiblePosition(
      Position(owner_element_parent, owner_element_node_index + 1),
      TextAffinity::kUpstreamIfPossible);

  SelectionInDOMTree::Builder builder;
  builder
      .SetBaseAndExtentDeprecated(before_owner_element.DeepEquivalent(),
                                  after_owner_element.DeepEquivalent())
      .SetAffinity(before_owner_element.Affinity());

  VisibleSelection new_selection = CreateVisibleSelection(builder.Build());
  page->GetFocusController().SetFocusedFrame(parent);
  if (!new_selection.IsNone() &&
      new_selection.IsValidFor(*(ToLocalFrame(parent)->GetDocument()))) {
    ToLocalFrame(parent)->Selection().SetSelectionAndEndTyping(
        new_selection.AsSelection());
  }
}
