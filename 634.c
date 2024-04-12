void CopyReplacedNavigationEntryDataIfPreviouslyEmpty(
    const NavigationEntryImpl& replaced_entry,
    NavigationEntryImpl* output_entry) {
  if (output_entry->GetReplacedEntryData().has_value())
    return;

  ReplacedNavigationEntryData data;
  data.first_committed_url = replaced_entry.GetURL();
  data.first_timestamp = replaced_entry.GetTimestamp();
  data.first_transition_type = replaced_entry.GetTransitionType();
  output_entry->SetReplacedEntryData(data);
}
