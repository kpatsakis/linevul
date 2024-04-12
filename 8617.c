PermissionsData::PageAccess PermissionsData::CanRunOnPage(
    const GURL& document_url,
    int tab_id,
    const URLPatternSet& permitted_url_patterns,
    const URLPatternSet& withheld_url_patterns,
    const URLPatternSet* tab_url_patterns,
    std::string* error) const {
  runtime_lock_.AssertAcquired();
  if (location_ != Manifest::COMPONENT &&
      IsPolicyBlockedHostUnsafe(document_url)) {
    if (error)
      *error = extension_misc::kPolicyBlockedScripting;
    return PageAccess::kDenied;
  }

  if (IsRestrictedUrl(document_url, error))
    return PageAccess::kDenied;

  if (tab_url_patterns && tab_url_patterns->MatchesURL(document_url))
    return PageAccess::kAllowed;

  if (permitted_url_patterns.MatchesURL(document_url))
    return PageAccess::kAllowed;

  if (withheld_url_patterns.MatchesURL(document_url))
    return PageAccess::kWithheld;

  if (error) {
    if (active_permissions_unsafe_->HasAPIPermission(APIPermission::kTab)) {
      *error = ErrorUtils::FormatErrorMessage(
          manifest_errors::kCannotAccessPageWithUrl, document_url.spec());
    } else {
      *error = manifest_errors::kCannotAccessPage;
    }
  }

  return PageAccess::kDenied;
}
