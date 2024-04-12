static bool IsNodeOnAncestorChain(const ClipPaintPropertyNode& find,
                                  const ClipPaintPropertyNode& current,
                                  const ClipPaintPropertyNode& ancestor) {
  DCHECK(ancestor.IsAncestorOf(current));

  for (const auto* node = &current; node != &ancestor; node = node->Parent()) {
    if (node == &find)
      return true;
  }
  return false;
}
