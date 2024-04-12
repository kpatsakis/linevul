void AppCacheUpdateJob::NotifySingleHost(
    AppCacheHost* host,
    blink::mojom::AppCacheEventID event_id) {
  host->frontend()->EventRaised(event_id);
}
