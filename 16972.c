DEFINE_TRACE(DocumentLoader) {
  visitor->Trace(frame_);
  visitor->Trace(fetcher_);
  visitor->Trace(main_resource_);
  visitor->Trace(history_item_);
  visitor->Trace(writer_);
  visitor->Trace(subresource_filter_);
  visitor->Trace(document_load_timing_);
  visitor->Trace(application_cache_host_);
  visitor->Trace(content_security_policy_);
  RawResourceClient::Trace(visitor);
}
