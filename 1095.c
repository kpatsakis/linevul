void ServiceWorkerHandler::ClearForceUpdate() {
  if (context_)
    context_->SetForceUpdateOnPageLoad(false);
}
