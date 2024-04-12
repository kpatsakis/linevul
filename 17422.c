bool ChromeContentBrowserClient::CanIgnoreCertificateErrorIfNeeded() {
  return base::CommandLine::ForCurrentProcess()->HasSwitch(
      switches::kUserDataDir);
}
