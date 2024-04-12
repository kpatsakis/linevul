void WebContext::setLegacyUserAgentOverrideEnabled(bool enabled) {
  if (IsInitialized()) {
    UserAgentSettings::Get(context_.get())->SetLegacyUserAgentOverrideEnabled(
        enabled);
  } else {
    construct_props_->legacy_user_agent_override_enabled = enabled;
  }
}
