static void CopySmiToDoubleElements(FixedArrayBase* from_base,
 uint32_t from_start,
 FixedArrayBase* to_base, uint32_t to_start,
 int raw_copy_size) {
 DisallowHeapAllocation no_allocation;
 int copy_size = raw_copy_size;
 if (raw_copy_size < 0) {
    DCHECK(raw_copy_size == ElementsAccessor::kCopyToEnd ||
           raw_copy_size == ElementsAccessor::kCopyToEndAndInitializeToHole);
    copy_size = from_base->length() - from_start;
 if (raw_copy_size == ElementsAccessor::kCopyToEndAndInitializeToHole) {
 for (int i = to_start + copy_size; i < to_base->length(); ++i) {
 FixedDoubleArray::cast(to_base)->set_the_hole(i);
 }
 }
 }
  DCHECK((copy_size + static_cast<int>(to_start)) <= to_base->length() &&
 (copy_size + static_cast<int>(from_start)) <= from_base->length());
 if (copy_size == 0) return;
 FixedArray* from = FixedArray::cast(from_base);
 FixedDoubleArray* to = FixedDoubleArray::cast(to_base);
 Object* the_hole = from->GetHeap()->the_hole_value();
 for (uint32_t from_end = from_start + static_cast<uint32_t>(copy_size);
       from_start < from_end; from_start++, to_start++) {
 Object* hole_or_smi = from->get(from_start);
 if (hole_or_smi == the_hole) {
      to->set_the_hole(to_start);
 } else {
      to->set(to_start, Smi::cast(hole_or_smi)->value());
 }
 }
}
