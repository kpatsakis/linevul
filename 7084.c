void GotUsageAndQuotaDataCallback(
    std::unique_ptr<StorageHandler::GetUsageAndQuotaCallback> callback,
    blink::mojom::QuotaStatusCode code,
    int64_t usage,
    int64_t quota,
    base::flat_map<storage::QuotaClient::ID, int64_t> usage_breakdown) {
  DCHECK_CURRENTLY_ON(BrowserThread::IO);
  BrowserThread::PostTask(
      BrowserThread::UI, FROM_HERE,
      base::BindOnce(ReportUsageAndQuotaDataOnUIThread,
                     base::Passed(std::move(callback)), code, usage, quota,
                     std::move(usage_breakdown)));
}
