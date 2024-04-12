bool ScrollAnchor::FindAnchorRecursive(LayoutObject* candidate) {
  ExamineResult result = Examine(candidate);
  if (result.viable) {
    anchor_object_ = candidate;
    corner_ = result.corner;
  }

  if (result.status == kReturn)
    return true;

  if (result.status == kSkip)
    return false;

  for (LayoutObject* child = candidate->SlowFirstChild(); child;
       child = child->NextSibling()) {
    if (FindAnchorRecursive(child))
      return true;
  }

  if (auto* layouy_block = DynamicTo<LayoutBlock>(candidate)) {
    if (TrackedLayoutBoxListHashSet* positioned_descendants =
            layouy_block->PositionedObjects()) {
      for (LayoutBox* descendant : *positioned_descendants) {
        if (descendant->Parent() != candidate) {
          if (FindAnchorRecursive(descendant))
            return true;
        }
      }
    }
  }

  if (result.status == kConstrain)
    return true;

  DCHECK_EQ(result.status, kContinue);
  return false;
}
