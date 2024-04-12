bool AutocompleteEditModel::AcceptCurrentInstantPreview() {
  return InstantController::CommitIfCurrent(controller_->GetInstant());
}
