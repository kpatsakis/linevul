void WebContentsImpl::OnEnumerateDirectory(RenderViewHostImpl* source,
                                           int request_id,
                                           const base::FilePath& path) {
  if (!delegate_)
    return;

  ChildProcessSecurityPolicyImpl* policy =
      ChildProcessSecurityPolicyImpl::GetInstance();
  if (policy->CanReadFile(source->GetProcess()->GetID(), path)) {
    delegate_->EnumerateDirectory(this, request_id, path);
  }
}
