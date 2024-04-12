int PageInfoUI::GetConnectionIconID(PageInfo::SiteConnectionStatus status) {
  int resource_id = IDR_PAGEINFO_INFO;
  switch (status) {
    case PageInfo::SITE_CONNECTION_STATUS_UNKNOWN:
    case PageInfo::SITE_CONNECTION_STATUS_INTERNAL_PAGE:
      break;
    case PageInfo::SITE_CONNECTION_STATUS_ENCRYPTED:
      resource_id = IDR_PAGEINFO_GOOD;
      break;
    case PageInfo::SITE_CONNECTION_STATUS_INSECURE_PASSIVE_SUBRESOURCE:
    case PageInfo::SITE_CONNECTION_STATUS_INSECURE_FORM_ACTION:
      resource_id = IDR_PAGEINFO_WARNING_MINOR;
      break;
    case PageInfo::SITE_CONNECTION_STATUS_UNENCRYPTED:
      resource_id = IDR_PAGEINFO_WARNING_MAJOR;
      break;
    case PageInfo::SITE_CONNECTION_STATUS_INSECURE_ACTIVE_SUBRESOURCE:
    case PageInfo::SITE_CONNECTION_STATUS_ENCRYPTED_ERROR:
      resource_id = IDR_PAGEINFO_BAD;
      break;
  }
  return resource_id;
}
