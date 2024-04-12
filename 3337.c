bool SiteInstanceImpl::IsSameWebSite(BrowserContext* browser_context,
                                     const GURL& real_src_url,
                                     const GURL& real_dest_url,
                                     bool should_compare_effective_urls) {
  GURL src_url =
      should_compare_effective_urls
          ? SiteInstanceImpl::GetEffectiveURL(browser_context, real_src_url)
          : real_src_url;
  GURL dest_url =
      should_compare_effective_urls
          ? SiteInstanceImpl::GetEffectiveURL(browser_context, real_dest_url)
          : real_dest_url;


  if (IsRendererDebugURL(src_url) || IsRendererDebugURL(dest_url))
    return true;

  if (!src_url.is_valid() || !dest_url.is_valid())
    return false;

  GURL blank_page(url::kAboutBlankURL);
  if (dest_url == blank_page)
    return true;

  if (src_url.EqualsIgnoringRef(dest_url))
    return true;

  url::Origin src_origin = url::Origin::Create(src_url);
  url::Origin dest_origin = url::Origin::Create(dest_url);

  if (src_origin.scheme() != dest_origin.scheme())
    return false;

  if (!net::registry_controlled_domains::SameDomainOrHost(
          src_origin, dest_origin,
          net::registry_controlled_domains::INCLUDE_PRIVATE_REGISTRIES)) {
    return false;
  }

  if (src_origin == dest_origin)
    return true;
  auto* policy = ChildProcessSecurityPolicyImpl::GetInstance();
  url::Origin src_isolated_origin;
  url::Origin dest_isolated_origin;
  bool src_origin_is_isolated =
      policy->GetMatchingIsolatedOrigin(src_origin, &src_isolated_origin);
  bool dest_origin_is_isolated =
      policy->GetMatchingIsolatedOrigin(dest_origin, &dest_isolated_origin);
  if (src_origin_is_isolated || dest_origin_is_isolated) {
    return src_isolated_origin == dest_isolated_origin;
  }

  return true;
}
