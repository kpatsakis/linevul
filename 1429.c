void AutocompleteController::OnProviderUpdate(bool updated_matches) {
  CheckIfDone();
  if (!in_start_ && (updated_matches || done_))
     UpdateResult(false);
 }
