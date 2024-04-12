void InspectorNetworkAgent::WillLoadXHR(XMLHttpRequest* xhr,
                                        ThreadableLoaderClient* client,
                                        const AtomicString& method,
                                        const KURL& url,
                                        bool async,
                                        RefPtr<EncodedFormData> form_data,
                                        const HTTPHeaderMap& headers,
                                        bool include_credentials) {
  DCHECK(xhr);
  DCHECK(!pending_request_);
  pending_request_ = client;
  pending_request_type_ = InspectorPageAgent::kXHRResource;
  pending_xhr_replay_data_ = XHRReplayData::Create(
      xhr->GetExecutionContext(), method, UrlWithoutFragment(url), async,
      form_data.get(), include_credentials);
  for (const auto& header : headers)
    pending_xhr_replay_data_->AddHeader(header.key, header.value);
}
