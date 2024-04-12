void SBEntry::SetFullHashAt(int index, const SBFullHash& full_hash) {
  DCHECK(!IsPrefix());

  if (IsAdd())
    add_full_hashes_[index] = full_hash;
  else
    sub_full_hashes_[index].prefix = full_hash;
}
