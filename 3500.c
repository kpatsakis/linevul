bool AXLayoutObject::isVisited() const {
  return m_layoutObject->style()->isLink() &&
         m_layoutObject->style()->insideLink() ==
             EInsideLink::kInsideVisitedLink;
}
