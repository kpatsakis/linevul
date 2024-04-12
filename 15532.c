void RenderViewHost::FilterURL(const RenderProcessHost* process,
                               bool empty_allowed,
                               GURL* url) {
  RenderViewHostImpl::FilterURL(ChildProcessSecurityPolicyImpl::GetInstance(),
                                process, empty_allowed, url);
}
