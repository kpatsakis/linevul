void Document::DidRemoveText(const CharacterData& text,
                             unsigned offset,
                             unsigned length) {
  for (Range* range : ranges_)
    range->DidRemoveText(text, offset, length);
}
