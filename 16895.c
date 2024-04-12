void BackgroundLoaderOfflinerTest::OnCompletion(
    const SavePageRequest& request,
    Offliner::RequestStatus status) {
  DCHECK(!completion_callback_called_);  // Expect 1 callback per request.
  completion_callback_called_ = true;
  request_status_ = status;
}
