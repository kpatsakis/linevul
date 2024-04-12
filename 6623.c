  ConstructProperties()
      : max_cache_size_hint(0),
        cookie_policy(net::StaticCookiePolicy::ALLOW_ALL_COOKIES),
        session_cookie_mode(content::CookieStoreConfig::EPHEMERAL_SESSION_COOKIES),
        popup_blocker_enabled(true),
        devtools_enabled(false),
        devtools_port(-1),
        legacy_user_agent_override_enabled(false),
        do_not_track(false) {}
