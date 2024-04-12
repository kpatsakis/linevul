PageInfo::PageInfo(
    PageInfoUI* ui,
    Profile* profile,
    TabSpecificContentSettings* tab_specific_content_settings,
    content::WebContents* web_contents,
    const GURL& url,
    security_state::SecurityLevel security_level,
    const security_state::VisibleSecurityState& visible_security_state)
    : TabSpecificContentSettings::SiteDataObserver(
          tab_specific_content_settings),
      content::WebContentsObserver(web_contents),
      ui_(ui),
      show_info_bar_(false),
      site_url_(url),
      site_identity_status_(SITE_IDENTITY_STATUS_UNKNOWN),
      site_connection_status_(SITE_CONNECTION_STATUS_UNKNOWN),
      show_ssl_decision_revoke_button_(false),
      content_settings_(HostContentSettingsMapFactory::GetForProfile(profile)),
      chrome_ssl_host_state_delegate_(
          ChromeSSLHostStateDelegateFactory::GetForProfile(profile)),
      did_revoke_user_ssl_decisions_(false),
      profile_(profile),
      security_level_(security_state::NONE),
#if defined(FULL_SAFE_BROWSING)
      password_protection_service_(
          safe_browsing::ChromePasswordProtectionService::
              GetPasswordProtectionService(profile_)),
#endif
      show_change_password_buttons_(false),
      did_perform_action_(false) {
  ComputeUIInputs(url, security_level, visible_security_state);

  PresentSitePermissions();
  PresentSiteIdentity();
  PresentSiteData();
  PresentPageFeatureInfo();

  RecordPageInfoAction(PAGE_INFO_OPENED);

  start_time_ = base::TimeTicks::Now();
}
