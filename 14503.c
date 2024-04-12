void IndexedDBDatabase::ProcessRequestQueue() {
  if (processing_pending_requests_)
    return;

  DCHECK(!active_request_);
  DCHECK(!pending_requests_.empty());

  base::AutoReset<bool> processing(&processing_pending_requests_, true);
  do {
    active_request_ = std::move(pending_requests_.front());
    pending_requests_.pop();
    active_request_->Perform();
  } while (!active_request_ && !pending_requests_.empty());
}
