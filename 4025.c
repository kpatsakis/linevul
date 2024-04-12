void WebContentsImpl::DidGetRedirectForResourceRequest(
  const ResourceRedirectDetails& details) {
  for (auto& observer : observers_)
    observer.DidGetRedirectForResourceRequest(details);

  NotificationService::current()->Notify(
      NOTIFICATION_RESOURCE_RECEIVED_REDIRECT,
      Source<WebContents>(this),
      Details<const ResourceRedirectDetails>(&details));
}
