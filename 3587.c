bool MdmEnrollmentEnabled() {
  base::string16 mdm_url = GetMdmUrl();
  return !mdm_url.empty();
}
