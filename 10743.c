void RenderFrameHostImpl::OnUpdateEncoding(const std::string& encoding_name) {
  delegate_->UpdateEncoding(this, encoding_name);
}
