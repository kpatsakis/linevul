bool Document::IsTrustedTypesEnabledForDoc() const {
  return SecurityContext::RequireTrustedTypes() &&
         origin_trials::TrustedDOMTypesEnabled(this);
}
