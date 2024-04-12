void PushMessagingServiceImpl::UnsubscribeInternal(
    content::mojom::PushUnregistrationReason reason,
    const GURL& origin,
    int64_t service_worker_registration_id,
    const std::string& app_id,
    const std::string& sender_id,
    const UnregisterCallback& callback) {
  DCHECK(!app_id.empty() || (!origin.is_empty() &&
                             service_worker_registration_id !=
                                 -1 /* kInvalidServiceWorkerRegistrationId */))
      << "Need an app_id and/or origin+service_worker_registration_id";

  RecordUnsubscribeReason(reason);

  if (origin.is_empty() ||
      service_worker_registration_id ==
          -1 /* kInvalidServiceWorkerRegistrationId */) {
    DidClearPushSubscriptionId(reason, app_id, sender_id, callback);
    return;
  }
  ClearPushSubscriptionId(
      profile_, origin, service_worker_registration_id,
      base::Bind(&PushMessagingServiceImpl::DidClearPushSubscriptionId,
                 weak_factory_.GetWeakPtr(), reason, app_id, sender_id,
                 callback));
}
