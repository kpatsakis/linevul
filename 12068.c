bool ChromeContentBrowserClient::IsBuiltinComponent(
    content::BrowserContext* browser_context,
    const url::Origin& origin) {
#if BUILDFLAG(ENABLE_EXTENSIONS)
  return ChromeContentBrowserClientExtensionsPart::IsBuiltinComponent(
      browser_context, origin);
#else
  return false;
#endif
}
