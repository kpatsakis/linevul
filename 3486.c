IOThread::IOThread(
    PrefService* local_state,
    policy::PolicyService* policy_service,
    ChromeNetLog* net_log,
    extensions::EventRouterForwarder* extension_event_router_forwarder)
    : net_log_(net_log),
      extension_event_router_forwarder_(extension_event_router_forwarder),
      globals_(NULL),
      sdch_manager_(NULL),
      is_spdy_disabled_by_policy_(false),
      weak_factory_(this) {
#if !defined(OS_IOS) && !defined(OS_ANDROID)
#if defined(OS_WIN)
  if (!win8::IsSingleWindowMetroMode())
    net::ProxyResolverV8::RememberDefaultIsolate();
  else
    net::ProxyResolverV8::CreateIsolate();
#else
  net::ProxyResolverV8::RememberDefaultIsolate();
#endif
#endif
  auth_schemes_ = local_state->GetString(prefs::kAuthSchemes);
  negotiate_disable_cname_lookup_ = local_state->GetBoolean(
      prefs::kDisableAuthNegotiateCnameLookup);
  negotiate_enable_port_ = local_state->GetBoolean(
      prefs::kEnableAuthNegotiatePort);
  auth_server_whitelist_ = local_state->GetString(prefs::kAuthServerWhitelist);
  auth_delegate_whitelist_ = local_state->GetString(
      prefs::kAuthNegotiateDelegateWhitelist);
  gssapi_library_name_ = local_state->GetString(prefs::kGSSAPILibraryName);
  pref_proxy_config_tracker_.reset(
      ProxyServiceFactory::CreatePrefProxyConfigTrackerOfLocalState(
          local_state));
  ChromeNetworkDelegate::InitializePrefsOnUIThread(
      &system_enable_referrers_,
      NULL,
      NULL,
      local_state);
  ssl_config_service_manager_.reset(
      SSLConfigServiceManager::CreateDefaultManager(local_state));

  base::Value* dns_client_enabled_default = new base::FundamentalValue(
      chrome_browser_net::ConfigureAsyncDnsFieldTrial());
  local_state->SetDefaultPrefValue(prefs::kBuiltInDnsClientEnabled,
                                   dns_client_enabled_default);

  dns_client_enabled_.Init(prefs::kBuiltInDnsClientEnabled,
                           local_state,
                           base::Bind(&IOThread::UpdateDnsClientEnabled,
                                      base::Unretained(this)));
  dns_client_enabled_.MoveToThread(
      BrowserThread::GetMessageLoopProxyForThread(BrowserThread::IO));

#if defined(ENABLE_CONFIGURATION_POLICY)
  is_spdy_disabled_by_policy_ = policy_service->GetPolicies(
      policy::PolicyNamespace(policy::POLICY_DOMAIN_CHROME, std::string())).Get(
          policy::key::kDisableSpdy) != NULL;
#endif  // ENABLE_CONFIGURATION_POLICY

  BrowserThread::SetDelegate(BrowserThread::IO, this);
}
