infobars::InfoBar* ExtensionDevToolsInfoBarDelegate::Create(
    RenderViewHost* rvh,
    const std::string& client_name) {
  if (!rvh)
    return NULL;

  WebContents* web_contents = WebContents::FromRenderViewHost(rvh);
  if (!web_contents)
    return NULL;

  InfoBarService* infobar_service =
      InfoBarService::FromWebContents(web_contents);
  if (!infobar_service)
    return NULL;

  return infobar_service->AddInfoBar(ConfirmInfoBarDelegate::CreateInfoBar(
      scoped_ptr<ConfirmInfoBarDelegate>(
          new ExtensionDevToolsInfoBarDelegate(client_name))));
}
