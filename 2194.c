void Document::NodeWillBeRemoved(Node& n) {
  for (NodeIterator* ni : node_iterators_)
    ni->NodeWillBeRemoved(n);

  for (Range* range : ranges_)
    range->NodeWillBeRemoved(n);

  NotifyNodeWillBeRemoved(n);

  if (ContainsV1ShadowTree())
    n.CheckSlotChangeBeforeRemoved();

  if (n.InActiveDocument() && n.IsElementNode())
    GetStyleEngine().ElementWillBeRemoved(ToElement(n));
}
