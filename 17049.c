 void ChromeExtensionsDispatcherDelegate::PopulateSourceMap(
    extensions::ResourceBundleSourceMap* source_map) {
  source_map->RegisterSource("app", IDR_APP_CUSTOM_BINDINGS_JS);
  source_map->RegisterSource("automation", IDR_AUTOMATION_CUSTOM_BINDINGS_JS);
  source_map->RegisterSource("automationEvent", IDR_AUTOMATION_EVENT_JS);
  source_map->RegisterSource("automationNode", IDR_AUTOMATION_NODE_JS);
  source_map->RegisterSource("browserAction",
                             IDR_BROWSER_ACTION_CUSTOM_BINDINGS_JS);
  source_map->RegisterSource("certificateProvider",
                             IDR_CERTIFICATE_PROVIDER_CUSTOM_BINDINGS_JS);
  source_map->RegisterSource("declarativeContent",
                             IDR_DECLARATIVE_CONTENT_CUSTOM_BINDINGS_JS);
  source_map->RegisterSource("desktopCapture",
                             IDR_DESKTOP_CAPTURE_CUSTOM_BINDINGS_JS);
  source_map->RegisterSource("developerPrivate",
                             IDR_DEVELOPER_PRIVATE_CUSTOM_BINDINGS_JS);
  source_map->RegisterSource("downloads", IDR_DOWNLOADS_CUSTOM_BINDINGS_JS);
  source_map->RegisterSource("enterprise.platformKeys",
                             IDR_ENTERPRISE_PLATFORM_KEYS_CUSTOM_BINDINGS_JS);
  source_map->RegisterSource("enterprise.platformKeys.internalAPI",
                             IDR_ENTERPRISE_PLATFORM_KEYS_INTERNAL_API_JS);
  source_map->RegisterSource("enterprise.platformKeys.KeyPair",
                             IDR_ENTERPRISE_PLATFORM_KEYS_KEY_PAIR_JS);
  source_map->RegisterSource("enterprise.platformKeys.SubtleCrypto",
                             IDR_ENTERPRISE_PLATFORM_KEYS_SUBTLE_CRYPTO_JS);
  source_map->RegisterSource("enterprise.platformKeys.Token",
                             IDR_ENTERPRISE_PLATFORM_KEYS_TOKEN_JS);
  source_map->RegisterSource("feedbackPrivate",
                             IDR_FEEDBACK_PRIVATE_CUSTOM_BINDINGS_JS);
  source_map->RegisterSource("fileBrowserHandler",
                             IDR_FILE_BROWSER_HANDLER_CUSTOM_BINDINGS_JS);
  source_map->RegisterSource("fileManagerPrivate",
                             IDR_FILE_MANAGER_PRIVATE_CUSTOM_BINDINGS_JS);
  source_map->RegisterSource("fileSystem", IDR_FILE_SYSTEM_CUSTOM_BINDINGS_JS);
  source_map->RegisterSource("fileSystemProvider",
                             IDR_FILE_SYSTEM_PROVIDER_CUSTOM_BINDINGS_JS);
  source_map->RegisterSource("gcm", IDR_GCM_CUSTOM_BINDINGS_JS);
  source_map->RegisterSource("identity", IDR_IDENTITY_CUSTOM_BINDINGS_JS);
  source_map->RegisterSource("imageWriterPrivate",
                             IDR_IMAGE_WRITER_PRIVATE_CUSTOM_BINDINGS_JS);
  source_map->RegisterSource("input.ime", IDR_INPUT_IME_CUSTOM_BINDINGS_JS);
  source_map->RegisterSource("logPrivate", IDR_LOG_PRIVATE_CUSTOM_BINDINGS_JS);
  source_map->RegisterSource("mediaGalleries",
                             IDR_MEDIA_GALLERIES_CUSTOM_BINDINGS_JS);
  source_map->RegisterSource("notifications",
                             IDR_NOTIFICATIONS_CUSTOM_BINDINGS_JS);
  source_map->RegisterSource("omnibox", IDR_OMNIBOX_CUSTOM_BINDINGS_JS);
  source_map->RegisterSource("pageAction", IDR_PAGE_ACTION_CUSTOM_BINDINGS_JS);
  source_map->RegisterSource("pageCapture",
                             IDR_PAGE_CAPTURE_CUSTOM_BINDINGS_JS);
  source_map->RegisterSource("platformKeys",
                             IDR_PLATFORM_KEYS_CUSTOM_BINDINGS_JS);
  source_map->RegisterSource("platformKeys.getPublicKey",
                             IDR_PLATFORM_KEYS_GET_PUBLIC_KEY_JS);
  source_map->RegisterSource("platformKeys.internalAPI",
                             IDR_PLATFORM_KEYS_INTERNAL_API_JS);
  source_map->RegisterSource("platformKeys.Key", IDR_PLATFORM_KEYS_KEY_JS);
  source_map->RegisterSource("platformKeys.SubtleCrypto",
                             IDR_PLATFORM_KEYS_SUBTLE_CRYPTO_JS);
  source_map->RegisterSource("platformKeys.utils", IDR_PLATFORM_KEYS_UTILS_JS);
  source_map->RegisterSource("syncFileSystem",
                             IDR_SYNC_FILE_SYSTEM_CUSTOM_BINDINGS_JS);
  source_map->RegisterSource("systemIndicator",
                             IDR_SYSTEM_INDICATOR_CUSTOM_BINDINGS_JS);
  source_map->RegisterSource("tabCapture", IDR_TAB_CAPTURE_CUSTOM_BINDINGS_JS);
  source_map->RegisterSource("tabs", IDR_TABS_CUSTOM_BINDINGS_JS);
  source_map->RegisterSource("terminalPrivate",
                             IDR_TERMINAL_PRIVATE_CUSTOM_BINDINGS_JS);
  source_map->RegisterSource("tts", IDR_TTS_CUSTOM_BINDINGS_JS);
  source_map->RegisterSource("ttsEngine", IDR_TTS_ENGINE_CUSTOM_BINDINGS_JS);
#if defined(ENABLE_WEBRTC)
  source_map->RegisterSource("cast.streaming.rtpStream",
                             IDR_CAST_STREAMING_RTP_STREAM_CUSTOM_BINDINGS_JS);
  source_map->RegisterSource("cast.streaming.session",
                             IDR_CAST_STREAMING_SESSION_CUSTOM_BINDINGS_JS);
  source_map->RegisterSource(
      "cast.streaming.udpTransport",
      IDR_CAST_STREAMING_UDP_TRANSPORT_CUSTOM_BINDINGS_JS);
  source_map->RegisterSource(
      "cast.streaming.receiverSession",
      IDR_CAST_STREAMING_RECEIVER_SESSION_CUSTOM_BINDINGS_JS);
#endif
  source_map->RegisterSource(
      "webrtcDesktopCapturePrivate",
      IDR_WEBRTC_DESKTOP_CAPTURE_PRIVATE_CUSTOM_BINDINGS_JS);
  source_map->RegisterSource("webstore", IDR_WEBSTORE_CUSTOM_BINDINGS_JS);

  source_map->RegisterSource("ChromeSetting", IDR_CHROME_SETTING_JS);
  source_map->RegisterSource("ContentSetting", IDR_CONTENT_SETTING_JS);
  source_map->RegisterSource("ChromeDirectSetting",
                             IDR_CHROME_DIRECT_SETTING_JS);

  source_map->RegisterSource("fileEntryBindingUtil",
                             IDR_FILE_ENTRY_BINDING_UTIL_JS);
  source_map->RegisterSource("tagWatcher", IDR_TAG_WATCHER_JS);
  source_map->RegisterSource("chromeWebViewInternal",
                             IDR_CHROME_WEB_VIEW_INTERNAL_CUSTOM_BINDINGS_JS);
  source_map->RegisterSource("chromeWebView", IDR_CHROME_WEB_VIEW_JS);
}
