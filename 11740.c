void ResourceMultiBufferDataProvider::DidFail(const WebURLError& error) {
  DVLOG(1) << "didFail: reason=" << error.reason();
  DCHECK(active_loader_.get());
  active_loader_.reset();

  if (retries_ < kMaxRetries && pos_ != 0) {
    retries_++;
    base::ThreadTaskRunnerHandle::Get()->PostDelayedTask(
        FROM_HERE,
        base::Bind(&ResourceMultiBufferDataProvider::Start,
                   weak_factory_.GetWeakPtr()),
        base::TimeDelta::FromMilliseconds(
            kLoaderFailedRetryDelayMs + kAdditionalDelayPerRetryMs * retries_));
  } else {
    url_data_->Fail();
  }
}
