void PageInfo::UpdateSecurityState(
    security_state::SecurityLevel security_level,
    const security_state::VisibleSecurityState& visible_security_state) {
  ComputeUIInputs(site_url_, security_level, visible_security_state);
  PresentSiteIdentity();
}
