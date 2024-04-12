void TextTrackCueList::RemoveAll() {
  if (list_.IsEmpty())
    return;

  first_invalid_index_ = 0;
  for (auto& cue : list_)
    cue->InvalidateCueIndex();
  Clear();
}
