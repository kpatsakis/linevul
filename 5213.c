bool ChromeContentBrowserClient::AllowPepperSocketAPI(
    content::BrowserContext* browser_context,
    const GURL& url,
    const content::SocketPermissionRequest& params) {
  if (!url.is_valid())
    return false;

  std::string host = url.host();
  if (url.SchemeIs(extensions::kExtensionScheme) &&
      allowed_socket_origins_.count(host)) {
    return true;
  }

  Profile* profile = Profile::FromBrowserContext(browser_context);
  const Extension* extension = NULL;
  ExtensionService* extension_service = !profile ? NULL :
      extensions::ExtensionSystem::Get(profile)->extension_service();
  if (extension_service) {
    extension = extension_service->extensions()->
        GetExtensionOrAppByURL(ExtensionURLInfo(url));
  }

  const CommandLine& command_line = *CommandLine::ForCurrentProcess();
  std::string allowed_list =
      command_line.GetSwitchValueASCII(switches::kAllowNaClSocketAPI);
  if (allowed_list == "*") {
    return extension &&
        (extension->GetType() == Manifest::TYPE_LEGACY_PACKAGED_APP ||
         extension->GetType() == Manifest::TYPE_PLATFORM_APP);
  } else if (!allowed_list.empty()) {
    base::StringTokenizer t(allowed_list, ",");
    while (t.GetNext()) {
      if (t.token() == host)
        return true;
    }
  }

  if (!extension)
    return false;

  extensions::SocketPermission::CheckParam extension_params(
      params.type, params.host, params.port);
  if (extension->CheckAPIPermissionWithParam(APIPermission::kSocket,
                                             &extension_params))
    return true;

  return false;
}
