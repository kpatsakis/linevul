void Range::setEnd(const Position& end, ExceptionCode& ec)
{
    Position parentAnchored = end.parentAnchoredEquivalent();
    setEnd(parentAnchored.containerNode(), parentAnchored.offsetInContainerNode(), ec);
}
