void UrlFetcher::Core::Start(const UrlFetcher::DoneCallback& done_callback) {
  done_callback_ = done_callback;
  network_task_runner_ = request_context_getter_->GetNetworkTaskRunner();
  DCHECK(network_task_runner_);
  network_task_runner_->PostTask(FROM_HERE, base::Bind(
      &UrlFetcher::Core::DoStart, this));
}
