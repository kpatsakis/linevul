Response ServiceWorkerHandler::SkipWaiting(const std::string& scope_url) {
  if (!enabled_)
    return CreateDomainNotEnabledErrorResponse();
  if (!context_)
    return CreateContextErrorResponse();
  context_->SkipWaitingWorker(GURL(scope_url));
  return Response::OK();
}
