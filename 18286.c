void NormalPage::checkAndMarkPointer(Visitor* visitor, Address address) {
#if DCHECK_IS_ON()
  DCHECK(contains(address));
#endif
  HeapObjectHeader* header = findHeaderFromAddress(address);
  if (!header)
    return;
  markPointer(visitor, header);
}
