bool NavigationControllerImpl::IsUnmodifiedBlankTab() const {
  return IsInitialNavigation() &&
         !GetLastCommittedEntry() &&
         !delegate_->HasAccessedInitialDocument();
}
