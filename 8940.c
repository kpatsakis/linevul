void ChromeContentBrowserClient::OverrideWebkitPrefs(
    RenderViewHost* rvh, WebPreferences* web_prefs) {
  Profile* profile = Profile::FromBrowserContext(
      rvh->GetProcess()->GetBrowserContext());
  PrefService* prefs = profile->GetPrefs();

#if !defined(OS_ANDROID)
  FontFamilyCache::FillFontFamilyMap(profile,
                                     prefs::kWebKitStandardFontFamilyMap,
                                     &web_prefs->standard_font_family_map);
  FontFamilyCache::FillFontFamilyMap(profile,
                                     prefs::kWebKitFixedFontFamilyMap,
                                     &web_prefs->fixed_font_family_map);
  FontFamilyCache::FillFontFamilyMap(profile,
                                     prefs::kWebKitSerifFontFamilyMap,
                                     &web_prefs->serif_font_family_map);
  FontFamilyCache::FillFontFamilyMap(profile,
                                     prefs::kWebKitSansSerifFontFamilyMap,
                                     &web_prefs->sans_serif_font_family_map);
  FontFamilyCache::FillFontFamilyMap(profile,
                                     prefs::kWebKitCursiveFontFamilyMap,
                                     &web_prefs->cursive_font_family_map);
  FontFamilyCache::FillFontFamilyMap(profile,
                                     prefs::kWebKitFantasyFontFamilyMap,
                                     &web_prefs->fantasy_font_family_map);
  FontFamilyCache::FillFontFamilyMap(profile,
                                     prefs::kWebKitPictographFontFamilyMap,
                                     &web_prefs->pictograph_font_family_map);

  web_prefs->default_font_size =
      prefs->GetInteger(prefs::kWebKitDefaultFontSize);
  web_prefs->default_fixed_font_size =
      prefs->GetInteger(prefs::kWebKitDefaultFixedFontSize);
  web_prefs->minimum_font_size =
      prefs->GetInteger(prefs::kWebKitMinimumFontSize);
  web_prefs->minimum_logical_font_size =
      prefs->GetInteger(prefs::kWebKitMinimumLogicalFontSize);
#endif

  web_prefs->default_encoding = prefs->GetString(prefs::kDefaultCharset);

  web_prefs->dom_paste_enabled =
      prefs->GetBoolean(prefs::kWebKitDomPasteEnabled);
  web_prefs->javascript_can_access_clipboard =
      prefs->GetBoolean(prefs::kWebKitJavascriptCanAccessClipboard);
  web_prefs->tabs_to_links = prefs->GetBoolean(prefs::kWebkitTabsToLinks);

  if (!prefs->GetBoolean(prefs::kWebKitJavascriptEnabled))
    web_prefs->javascript_enabled = false;

  base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();
  if (!prefs->GetBoolean(prefs::kWebKitWebSecurityEnabled)) {
    web_prefs->web_security_enabled = false;
  } else if (!web_prefs->web_security_enabled &&
             command_line->HasSwitch(switches::kDisableWebSecurity) &&
             !command_line->HasSwitch(switches::kUserDataDir)) {
    LOG(ERROR) << "Web security may only be disabled if '--user-data-dir' is "
               "also specified.";
    web_prefs->web_security_enabled = true;
  }

  if (!prefs->GetBoolean(prefs::kWebKitPluginsEnabled))
    web_prefs->plugins_enabled = false;
  web_prefs->loads_images_automatically =
      prefs->GetBoolean(prefs::kWebKitLoadsImagesAutomatically);

  if (prefs->GetBoolean(prefs::kDisable3DAPIs)) {
    web_prefs->webgl1_enabled = false;
    web_prefs->webgl2_enabled = false;
  }

  web_prefs->allow_running_insecure_content =
      prefs->GetBoolean(prefs::kWebKitAllowRunningInsecureContent);
#if defined(OS_ANDROID)
  web_prefs->font_scale_factor =
      static_cast<float>(prefs->GetDouble(prefs::kWebKitFontScaleFactor));
  web_prefs->device_scale_adjustment = GetDeviceScaleAdjustment();
  web_prefs->force_enable_zoom =
      prefs->GetBoolean(prefs::kWebKitForceEnableZoom);
#endif

#if defined(OS_ANDROID)
  web_prefs->password_echo_enabled =
      prefs->GetBoolean(prefs::kWebKitPasswordEchoEnabled);
#else
  web_prefs->password_echo_enabled = browser_defaults::kPasswordEchoEnabled;
#endif

  web_prefs->text_areas_are_resizable =
      prefs->GetBoolean(prefs::kWebKitTextAreasAreResizable);
  web_prefs->hyperlink_auditing_enabled =
      prefs->GetBoolean(prefs::kEnableHyperlinkAuditing);

#if BUILDFLAG(ENABLE_EXTENSIONS)
  std::string image_animation_policy =
      prefs->GetString(prefs::kAnimationPolicy);
  if (image_animation_policy == kAnimationPolicyOnce)
    web_prefs->animation_policy =
        content::IMAGE_ANIMATION_POLICY_ANIMATION_ONCE;
  else if (image_animation_policy == kAnimationPolicyNone)
    web_prefs->animation_policy = content::IMAGE_ANIMATION_POLICY_NO_ANIMATION;
  else
    web_prefs->animation_policy = content::IMAGE_ANIMATION_POLICY_ALLOWED;
#endif

  web_prefs->default_encoding =
      base::GetCanonicalEncodingNameByAliasName(web_prefs->default_encoding);
  if (web_prefs->default_encoding.empty()) {
    prefs->ClearPref(prefs::kDefaultCharset);
    web_prefs->default_encoding = prefs->GetString(prefs::kDefaultCharset);
  }
  DCHECK(!web_prefs->default_encoding.empty());

  if (base::CommandLine::ForCurrentProcess()->HasSwitch(
          switches::kEnablePotentiallyAnnoyingSecurityFeatures)) {
    web_prefs->disable_reading_from_canvas = true;
    web_prefs->strict_mixed_content_checking = true;
    web_prefs->strict_powerful_feature_restrictions = true;
  }

  web_prefs->data_saver_enabled = GetDataSaverEnabledPref(prefs);

  web_prefs->data_saver_holdback_web_api_enabled =
      base::GetFieldTrialParamByFeatureAsBool(features::kDataSaverHoldback,
                                              "holdback_web", false);
  web_prefs->data_saver_holdback_media_api_enabled =
      base::GetFieldTrialParamByFeatureAsBool(features::kDataSaverHoldback,
                                              "holdback_media", true);

  content::WebContents* contents =
      content::WebContents::FromRenderViewHost(rvh);
  if (contents) {
#if defined(OS_ANDROID)
    TabAndroid* tab_android = TabAndroid::FromWebContents(contents);
    if (tab_android) {
      web_prefs->embedded_media_experience_enabled =
          tab_android->ShouldEnableEmbeddedMediaExperience();

      if (base::FeatureList::IsEnabled(
              features::kAllowAutoplayUnmutedInWebappManifestScope)) {
        web_prefs->media_playback_gesture_whitelist_scope =
            tab_android->GetWebappManifestScope();
      }

      web_prefs->picture_in_picture_enabled =
          tab_android->IsPictureInPictureEnabled();
    }
#endif  // defined(OS_ANDROID)

#if BUILDFLAG(ENABLE_EXTENSIONS)
    Browser* browser = chrome::FindBrowserWithWebContents(contents);
    if (browser && browser->hosted_app_controller() &&
        browser->hosted_app_controller()->created_for_installed_pwa()) {
      web_prefs->strict_mixed_content_checking = true;
    }
#endif

    web_prefs->immersive_mode_enabled = vr::VrTabHelper::IsInVr(contents);
  }

#if defined(OS_ANDROID)
  web_prefs->video_fullscreen_detection_enabled = true;

  web_prefs->enable_media_download_in_product_help =
      base::FeatureList::IsEnabled(
          feature_engagement::kIPHMediaDownloadFeature);
#endif  // defined(OS_ANDROID)

  if (base::FeatureList::IsEnabled(features::kLowPriorityIframes)) {
    std::string effective_connection_type_param =
        base::GetFieldTrialParamValueByFeature(
            features::kLowPriorityIframes,
            "max_effective_connection_type_threshold");

    base::Optional<net::EffectiveConnectionType> effective_connection_type =
        net::GetEffectiveConnectionTypeForName(effective_connection_type_param);
    if (effective_connection_type) {
      web_prefs->low_priority_iframes_threshold =
          effective_connection_type.value();
    }
  }

  if (base::FeatureList::IsEnabled(features::kLazyFrameLoading)) {
    const char* param_name =
        web_prefs->data_saver_enabled
            ? "lazy_frame_loading_distance_thresholds_px_by_ect"
            : "lazy_frame_loading_distance_thresholds_px_by_ect_with_data_"
              "saver_enabled";

    base::StringPairs pairs;
    base::SplitStringIntoKeyValuePairs(
        base::GetFieldTrialParamValueByFeature(features::kLazyFrameLoading,
                                               param_name),
        ':', ',', &pairs);

    for (const auto& pair : pairs) {
      base::Optional<net::EffectiveConnectionType> effective_connection_type =
          net::GetEffectiveConnectionTypeForName(pair.first);
      int value = 0;
      if (effective_connection_type && base::StringToInt(pair.second, &value)) {
        web_prefs->lazy_frame_loading_distance_thresholds_px
            [effective_connection_type.value()] = value;
      }
    }
  }

  if (base::FeatureList::IsEnabled(features::kLazyImageLoading)) {
    const char* param_name =
        web_prefs->data_saver_enabled
            ? "lazy_image_loading_distance_thresholds_px_by_ect"
            : "lazy_image_loading_distance_thresholds_px_by_ect_with_data_"
              "saver_enabled";

    base::StringPairs pairs;
    base::SplitStringIntoKeyValuePairs(
        base::GetFieldTrialParamValueByFeature(features::kLazyImageLoading,
                                               param_name),
        ':', ',', &pairs);

    for (const auto& pair : pairs) {
      base::Optional<net::EffectiveConnectionType> effective_connection_type =
          net::GetEffectiveConnectionTypeForName(pair.first);
      int value = 0;
      if (effective_connection_type && base::StringToInt(pair.second, &value)) {
        web_prefs->lazy_image_loading_distance_thresholds_px
            [effective_connection_type.value()] = value;
      }
    }
  }

  if (base::FeatureList::IsEnabled(
          features::kNetworkQualityEstimatorWebHoldback)) {
    std::string effective_connection_type_param =
        base::GetFieldTrialParamValueByFeature(
            features::kNetworkQualityEstimatorWebHoldback,
            "web_effective_connection_type_override");

    base::Optional<net::EffectiveConnectionType> effective_connection_type =
        net::GetEffectiveConnectionTypeForName(effective_connection_type_param);
    DCHECK(effective_connection_type_param.empty() ||
           effective_connection_type);
    if (effective_connection_type) {
      DCHECK_NE(net::EFFECTIVE_CONNECTION_TYPE_UNKNOWN,
                effective_connection_type.value());
      web_prefs->network_quality_estimator_web_holdback =
          effective_connection_type.value();
    }
  }

#if !defined(OS_ANDROID)
  if (IsAutoplayAllowedByPolicy(contents, prefs)) {
    web_prefs->autoplay_policy =
        content::AutoplayPolicy::kNoUserGestureRequired;
  } else if (base::FeatureList::IsEnabled(media::kAutoplayDisableSettings) &&
             web_prefs->autoplay_policy ==
                 content::AutoplayPolicy::kDocumentUserActivationRequired) {
    web_prefs->autoplay_policy =
        UnifiedAutoplayConfig::ShouldBlockAutoplay(profile)
            ? content::AutoplayPolicy::kDocumentUserActivationRequired
            : content::AutoplayPolicy::kNoUserGestureRequired;
  }
#endif  // !defined(OS_ANDROID)

  web_prefs->translate_service_available = TranslateService::IsAvailable(prefs);
  for (size_t i = 0; i < extra_parts_.size(); ++i)
    extra_parts_[i]->OverrideWebkitPrefs(rvh, web_prefs);
}
