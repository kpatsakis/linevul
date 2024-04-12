void WebContentsImpl::OnRegisterProtocolHandler(RenderFrameHostImpl* source,
                                                const std::string& protocol,
                                                const GURL& url,
                                                const base::string16& title,
                                                bool user_gesture) {
  if (!delegate_)
    return;

  ChildProcessSecurityPolicyImpl* policy =
      ChildProcessSecurityPolicyImpl::GetInstance();
  if (policy->IsPseudoScheme(protocol))
    return;

  delegate_->RegisterProtocolHandler(this, protocol, url, user_gesture);
}
