static LayoutBlockFlow* nonInlineBlockFlow(LayoutObject* object) {
  LayoutObject* current = object;
  while (current) {
    if (current->isLayoutBlockFlow()) {
      LayoutBlockFlow* blockFlow = toLayoutBlockFlow(current);
      if (!blockFlow->inlineBoxWrapper())
        return blockFlow;
    }
    current = current->parent();
  }

  ASSERT_NOT_REACHED();
  return nullptr;
}
