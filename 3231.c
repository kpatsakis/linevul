Range* Editor::FindStringAndScrollToVisible(const String& target,
                                            Range* previous_match,
                                            FindOptions options) {
  Range* next_match = FindRangeOfString(
      target, EphemeralRangeInFlatTree(previous_match), options);
  if (!next_match)
    return nullptr;

  Node* first_node = next_match->FirstNode();
  first_node->GetLayoutObject()->ScrollRectToVisible(
      LayoutRect(next_match->BoundingBox()),
      ScrollAlignment::kAlignCenterIfNeeded,
      ScrollAlignment::kAlignCenterIfNeeded, kUserScroll);
  first_node->GetDocument().SetSequentialFocusNavigationStartingPoint(
      first_node);

  return next_match;
}
