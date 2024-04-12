void ChromeContentBrowserClient::GetHardwareSecureDecryptionCaps(
    const std::string& key_system,
    const base::flat_set<media::CdmProxy::Protocol>& cdm_proxy_protocols,
    base::flat_set<media::VideoCodec>* video_codecs,
    base::flat_set<media::EncryptionMode>* encryption_schemes) {
#if defined(OS_WIN) && BUILDFLAG(ENABLE_LIBRARY_CDMS) && \
    BUILDFLAG(ENABLE_WIDEVINE)
  if (key_system == kWidevineKeySystem) {
    GetWidevineHardwareCaps(cdm_proxy_protocols, video_codecs,
                            encryption_schemes);
  }
#endif
}
