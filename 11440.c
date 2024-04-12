MetricsPrivateDelegate* ChromeExtensionsAPIClient::GetMetricsPrivateDelegate() {
  if (!metrics_private_delegate_)
    metrics_private_delegate_.reset(new ChromeMetricsPrivateDelegate());
  return metrics_private_delegate_.get();
}
