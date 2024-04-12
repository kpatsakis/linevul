HeapObjectHeader* NormalPage::FindHeaderFromAddress(Address address) {
  if (!ContainedInObjectPayload(address))
    return nullptr;
  if (ArenaForNormalPage()->IsInCurrentAllocationPointRegion(address))
    return nullptr;
  HeapObjectHeader* header = reinterpret_cast<HeapObjectHeader*>(
      object_start_bit_map()->FindHeader(address));
  if (header->IsFree())
    return nullptr;
  DCHECK_LT(0u, header->GcInfoIndex());
  DCHECK_GT(header->PayloadEnd(), address);
  return header;
}
