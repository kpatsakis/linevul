void ChromeExtensionsDispatcherDelegate::InitOriginPermissions(
    const extensions::Extension* extension,
    bool is_extension_active) {
  if (is_extension_active &&
      extension->permissions_data()->HasAPIPermission(
          extensions::APIPermission::kManagement)) {
    blink::WebSecurityPolicy::addOriginAccessWhitelistEntry(
        extension->url(),
        blink::WebString::fromUTF8(content::kChromeUIScheme),
        blink::WebString::fromUTF8(chrome::kChromeUIExtensionIconHost),
        false);
  }
}
