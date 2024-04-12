void ConfigureEntriesForRestore(
    std::vector<std::unique_ptr<NavigationEntryImpl>>* entries,
    RestoreType type) {
  for (size_t i = 0; i < entries->size(); ++i) {
    (*entries)[i]->SetTransitionType(ui::PAGE_TRANSITION_RELOAD);
    (*entries)[i]->set_restore_type(type);
    SetPageStateIfEmpty((*entries)[i].get());
  }
}
