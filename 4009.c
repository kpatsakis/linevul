ExtensionFunction::ResponseAction TabsSetZoomFunction::Run() {
  std::unique_ptr<tabs::SetZoom::Params> params(
      tabs::SetZoom::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params);

  int tab_id = params->tab_id ? *params->tab_id : -1;
  std::string error;
  WebContents* web_contents =
      GetTabsAPIDefaultWebContents(this, tab_id, &error);
  if (!web_contents)
    return RespondNow(Error(error));

  GURL url(web_contents->GetVisibleURL());
  if (extension()->permissions_data()->IsRestrictedUrl(url, &error))
    return RespondNow(Error(error));

  ZoomController* zoom_controller =
      ZoomController::FromWebContents(web_contents);
  double zoom_level = params->zoom_factor > 0
                          ? content::ZoomFactorToZoomLevel(params->zoom_factor)
                          : zoom_controller->GetDefaultZoomLevel();

  scoped_refptr<ExtensionZoomRequestClient> client(
      new ExtensionZoomRequestClient(extension()));
  if (!zoom_controller->SetZoomLevelByClient(zoom_level, client)) {
    return RespondNow(Error(tabs_constants::kCannotZoomDisabledTabError));
  }

  return RespondNow(NoArguments());
}
