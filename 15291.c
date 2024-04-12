void ImageLoader::DecodeRequest::ProcessForTask() {
  if (!loader_)
    return;

  DCHECK_EQ(state_, kPendingMicrotask);
  state_ = kPendingLoad;
  loader_->DispatchDecodeRequestsIfComplete();
}
