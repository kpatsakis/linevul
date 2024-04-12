void RenderViewHostImpl::FilterURL(ChildProcessSecurityPolicyImpl* policy,
                                   const RenderProcessHost* process,
                                   bool empty_allowed,
                                   GURL* url) {
  if (empty_allowed && url->is_empty())
    return;

  DCHECK(GURL(kSwappedOutURL) != *url);

  if (!url->is_valid()) {
    *url = GURL(chrome::kAboutBlankURL);
    return;
  }

  if (url->SchemeIs(chrome::kAboutScheme)) {
    *url = GURL(chrome::kAboutBlankURL);
  }

  bool non_web_url_in_guest = process->IsGuest() &&
      !(url->is_valid() && policy->IsWebSafeScheme(url->scheme()));

  if (non_web_url_in_guest || !policy->CanRequestURL(process->GetID(), *url)) {
    VLOG(1) << "Blocked URL " << url->spec();
    *url = GURL(chrome::kAboutBlankURL);
  }
}
