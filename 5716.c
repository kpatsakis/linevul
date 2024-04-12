bool IsGoogleDomainUrl(const GURL& url,
                       SubdomainPermission subdomain_permission,
                       PortPermission port_permission) {
  return IsValidURL(url, port_permission) &&
         IsCanonicalHostGoogleHostname(url.host_piece(), subdomain_permission);
}
