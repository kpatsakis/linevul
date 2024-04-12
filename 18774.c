void NavigationController::LoadEntry(NavigationEntry* entry) {
  ChildProcessSecurityPolicy *policy =
      ChildProcessSecurityPolicy::GetInstance();
  if (policy->IsDisabledScheme(entry->url().scheme()) ||
      policy->IsDisabledScheme(entry->virtual_url().scheme())) {
    VLOG(1) << "URL not loaded because the scheme is blocked by policy: "
            << entry->url();
    delete entry;
    return;
  }

  DiscardNonCommittedEntriesInternal();
  pending_entry_ = entry;
  content::NotificationService::current()->Notify(
      content::NOTIFICATION_NAV_ENTRY_PENDING,
      content::Source<NavigationController>(this),
      content::Details<NavigationEntry>(entry));
  NavigateToPendingEntry(NO_RELOAD);
}
