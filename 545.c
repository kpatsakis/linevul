void LocalFrameClientImpl::DidSetFramePolicyHeaders(
    SandboxFlags sandbox_flags,
    const ParsedFeaturePolicy& parsed_header) {
  if (web_frame_->Client()) {
    web_frame_->Client()->DidSetFramePolicyHeaders(
        static_cast<WebSandboxFlags>(sandbox_flags), parsed_header);
  }
}
