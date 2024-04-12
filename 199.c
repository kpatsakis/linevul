void TextTrack::AddListOfCues(
    HeapVector<Member<TextTrackCue>>& list_of_new_cues) {
  TextTrackCueList* cues = EnsureTextTrackCueList();

  for (auto& new_cue : list_of_new_cues) {
    new_cue->SetTrack(this);
    cues->Add(new_cue);
  }

  if (GetCueTimeline() && mode() != DisabledKeyword())
    GetCueTimeline()->AddCues(this, cues);
}
