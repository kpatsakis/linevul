void RenderFrameHostImpl::GrantFileAccessFromResourceRequestBody(
    const ResourceRequestBodyImpl& body) {
  GrantFileAccess(GetProcess()->GetID(), body.GetReferencedFiles());
}
